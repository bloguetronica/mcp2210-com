/* MCP2210 Commander - Version 1.0.0 for Debian Linux
   Copyright (c) 2023-2024 Samuel Lourenço

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation, either version 3 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <https://www.gnu.org/licenses/>.


   Please feel free to contact me via e-mail: samuel.fmlourenco@gmail.com */


// Includes
#include <QMessageBox>
#include "common.h"
#include "devicewindow.h"
#include "ui_devicewindow.h"

// Definitions
const int CENTRAL_HEIGHT = 701;
const int ERR_LIMIT = 10;

DeviceWindow::DeviceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeviceWindow)
{
    ui->setupUi(this);
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(update()));
}

DeviceWindow::~DeviceWindow()
{
    delete ui;
}

// Checks if the device window is currently fully enabled
bool DeviceWindow::isViewEnabled()
{
    return viewEnabled_;
}

// Opens the device and prepares the corresponding window
void DeviceWindow::openDevice(quint16 vid, quint16 pid, const QString &serialString)
{
    int err = mcp2210_.open(vid, pid, serialString);
    if (err == MCP2210::SUCCESS) {  // Device was successfully opened
        vid_ = vid;  // Pass VID
        pid_ = pid;  // and PID
        serialString_ = serialString;  // and the serial number as well
        readSettings();  // Read settings in volatile memory
        this->setWindowTitle(tr("MCP2210 Device (S/N: %1)").arg(serialString_));
        initializeView();
        timer_->start(100);  // Start the timer
    } else if (err == MCP2210::ERROR_INIT) {  // Failed to initialize libusb
        QMessageBox::critical(this, tr("Critical Error"), tr("Could not initialize libusb.\n\nThis is a critical error and execution will be aborted."));
        exit(EXIT_FAILURE);  // This error is critical because libusb failed to initialize
    } else {
        if (err == MCP2210::ERROR_NOT_FOUND) {  // Failed to find device
            QMessageBox::critical(this, tr("Error"), tr("Could not find device."));
        } else if (err == MCP2210::ERROR_BUSY) {  // Failed to claim interface
            QMessageBox::critical(this, tr("Error"), tr("Device is currently unavailable.\n\nPlease confirm that the device is not in use."));
        }
        this->deleteLater();  // Close window after the subsequent show() call
    }
}

void DeviceWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    this->setFixedHeight(ui->menuBar->height() + CENTRAL_HEIGHT + ui->statusBar->height());  // TODO
}

void DeviceWindow::on_actionAbout_triggered()
{
    showAboutDialog();  // See "common.h" and "common.cpp"
}

void DeviceWindow::on_actionInformation_triggered()
{
    if (informationDialog_.isNull()) {  // If the dialog is not open
        int errcnt = 0;
        QString errstr;
        QString manufacturerString = mcp2210_.getManufacturerDesc(errcnt, errstr);
        QString productString = mcp2210_.getProductDesc(errcnt, errstr);
        MCP2210::USBParameters usbParameters = mcp2210_.getUSBParameters(errcnt, errstr);
        if (validateOperation(tr("retrieve device information"), errcnt, errstr)) {
            informationDialog_ = new InformationDialog(this);
            informationDialog_->setAttribute(Qt::WA_DeleteOnClose);  // It is important to delete the dialog in memory once closed, in order to force the application to retrieve information about the device if the window is opened again
            informationDialog_->setWindowTitle(tr("Device Information (S/N: %1)").arg(serialString_));
            informationDialog_->setManufacturerValueLabelText(manufacturerString);
            informationDialog_->setProductValueLabelText(productString);
            informationDialog_->setSerialValueLabelText(serialString_);
            informationDialog_->setVIDValueLabelText(usbParameters.vid);
            informationDialog_->setPIDValueLabelText(usbParameters.pid);
            informationDialog_->setPowerModeValueLabelText(usbParameters.powmode);
            informationDialog_->setMaxPowerValueLabelText(usbParameters.maxpow);
            informationDialog_->setRemoteWakeUpCapableValueLabelText(usbParameters.rmwakeup);
            informationDialog_->show();
        }
    } else {
        informationDialog_->showNormal();  // Required if the dialog is minimized
        informationDialog_->activateWindow();  // Set focus on the previous dialog (dialog is raised and selected)
    }
}

void DeviceWindow::on_actionStatus_triggered()
{
    if (statusDialog_.isNull()) {  // If the dialog is not open
        int errcnt = 0;
        QString errstr;
        MCP2210::ChipStatus chipStatus = mcp2210_.getChipStatus(errcnt, errstr);
        if (validateOperation(tr("retrieve device status"), errcnt, errstr)) {
            statusDialog_ = new StatusDialog(this);
            statusDialog_->setAttribute(Qt::WA_DeleteOnClose);  // It is important to delete the dialog in memory once closed, in order to force the application to retrieve the device status if the window is opened again???
            statusDialog_->setWindowTitle(tr("Device Status (S/N: %1)").arg(serialString_));
            statusDialog_->setBusRequestValueLabelText(chipStatus.busreq);
            statusDialog_->setBusOwnerValueLabelText(chipStatus.busowner);
            statusDialog_->setPasswordStatusValueLabelText(chipStatus.pwok);
            statusDialog_->setPasswordTriesValueLabelText(chipStatus.pwtries);
            statusDialog_->show();
        }
    } else {
        statusDialog_->showNormal();  // Required if the dialog is minimized
        statusDialog_->activateWindow();  // Set focus on the previous dialog (dialog is raised and selected)
    }
}

// This is the main update routine
void DeviceWindow::update()
{
    // TODO
}

// Partially disables device window
void DeviceWindow::disableView()
{
    ui->actionInformation->setEnabled(false);
    ui->actionStatus->setEnabled(false);
    ui->actionChangePinFunctions->setEnabled(false);
    ui->actionClose->setText(tr("&Close Window"));
    ui->centralWidget->setEnabled(false);
    ui->checkBoxGPIO0->setStyleSheet("");
    ui->checkBoxGPIO1->setStyleSheet("");
    ui->checkBoxGPIO2->setStyleSheet("");
    ui->checkBoxGPIO3->setStyleSheet("");
    ui->checkBoxGPIO4->setStyleSheet("");
    ui->checkBoxGPIO5->setStyleSheet("");
    ui->checkBoxGPIO6->setStyleSheet("");
    ui->checkBoxGPIO7->setStyleSheet("");
    ui->checkBoxGPIO8->setStyleSheet("");
    ui->statusBar->setEnabled(false);
    viewEnabled_ = false;
}

// Initializes the GPIO controls
void DeviceWindow::initializeGPIOControls()
{
    // TODO
}

// This is the routine that is used to initialize the device window
void DeviceWindow::initializeView()
{
    initializeGPIOControls();
    // TODO
    viewEnabled_ = true;
}

// Reads settings from the MCP2210 volatile memory area
void DeviceWindow::readSettings()
{
    // TODO
}

// Checks for errors and validates (or ultimately halts) device operations
bool DeviceWindow::validateOperation(const QString &operation, int errcnt, QString errstr)
{
    bool retval;
    if (errcnt > 0) {
        if (mcp2210_.disconnected()) {
            timer_->stop();  // This prevents further errors
            disableView();  // Disable device window
            mcp2210_.close();
            QMessageBox::critical(this, tr("Error"), tr("Device disconnected.\n\nPlease reconnect it and try again."));
        } else {
            errstr.chop(1);  // Remove the last character, which is always a newline
            QMessageBox::critical(this, tr("Error"), tr("%1 operation returned the following error(s):\n– %2", "", errcnt).arg(operation, errstr.replace("\n", "\n– ")));
            erracc_ += errcnt;
            if (erracc_ > ERR_LIMIT) {  // If the session accumulated more errors than the limit set by "ERR_LIMIT" [10]
                timer_->stop();  // Again, this prevents further errors
                disableView();  // Disable device window
                mcp2210_.close();
                QMessageBox::critical(this, tr("Error"), tr("Detected too many errors."));
            }
        }
        retval = false;  // Failed validation
    } else {
        retval = true;  // Passed validation
    }
    return retval;
}
