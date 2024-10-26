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
        //readSettings();  // Read settings in volatile memory
        this->setWindowTitle(tr("MCP2210 Device (S/N: %1)").arg(serialString_));
        viewEnabled_ = true;
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
    this->setFixedHeight(ui->menuBar->height() + CENTRAL_HEIGHT);  // TODO
}

void DeviceWindow::on_actionAbout_triggered()
{
    showAboutDialog();  // See "common.h" and "common.cpp"
}

void DeviceWindow::on_actionStatus_triggered()
{
    if (statusDialog_.isNull()) {  // If the dialog is not open
        int errcnt = 0;
        QString errstr;
        MCP2210::ChipStatus chipStatus = mcp2210_.getChipStatus(errcnt, errstr);
        if (validOperation(tr("retrieve device status"), errcnt, errstr)) {
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

// Partially disables device window
void DeviceWindow::disableView()
{
    ui->actionInformation->setEnabled(false);
    ui->actionEditGPIOPinFunctions->setEnabled(false);
    ui->actionClose->setText(tr("&Close Window"));
    ui->centralWidget->setEnabled(false);
    /*ui->checkBoxGPIO0->setStyleSheet("");
    ui->checkBoxGPIO1->setStyleSheet("");
    ui->checkBoxGPIO2->setStyleSheet("");
    ui->checkBoxGPIO3->setStyleSheet("");
    ui->checkBoxGPIO4->setStyleSheet("");
    ui->checkBoxGPIO5->setStyleSheet("");
    ui->checkBoxGPIO6->setStyleSheet("");
    ui->checkBoxGPIO7->setStyleSheet("");
    ui->checkBoxGPIO8->setStyleSheet("");
    ui->checkBoxGPIO9->setStyleSheet("");
    ui->checkBoxGPIO10->setStyleSheet("");
    ui->lcdNumberCount->setStyleSheet("");*/
    ui->statusBar->setEnabled(false);
    viewEnabled_ = false;
}

// Checks for errors and validates (or ultimately halts) device operations
bool DeviceWindow::validOperation(const QString &operation, int errcnt, QString errstr)
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
                mcp2210_.close();  // Ensure that the device is freed, even if the previous device reset is not effective (cp2130_.reset() also frees the device interface, as an effect of re-enumeration)
                // It is essential that cp2130_.close() is called, since some important checks rely on cp2130_.isOpen() to retrieve a proper status
                QMessageBox::critical(this, tr("Error"), tr("Detected too many errors."));
            }
        }
        retval = false;  // Failed check
    } else {
        retval = true;  // Passed check
    }
    return retval;
}
