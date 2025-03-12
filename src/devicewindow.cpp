/* MCP2210 Commander - Version 1.0.0 for Debian Linux
   Copyright (c) 2023-2025 Samuel Lourenço

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
#include <QStringList>
#include "common.h"
#include "chipsettingsdialog.h"
#include "delaysdialog.h"
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
        initializeView();  // Initialize device window
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

void DeviceWindow::on_actionChipSettings_triggered()
{
    ChipSettingsDialog chipSettingsDialog(this);
    chipSettingsDialog.setGP0ComboBoxCurrentIndex(chipSettings_.gp0 == MCP2210::PCGPIO ? (0x01 & chipSettings_.gpdir) == 0x00 : chipSettings_.gp0 + 1);
    chipSettingsDialog.setGP0DefaultValueCheckBox((0x01 & chipSettings_.gpout) != 0x00);
    chipSettingsDialog.setGP1ComboBoxCurrentIndex(chipSettings_.gp1 == MCP2210::PCGPIO ? (0x02 & chipSettings_.gpdir) == 0x00 : chipSettings_.gp1 + 1);
    chipSettingsDialog.setGP1DefaultValueCheckBox((0x02 & chipSettings_.gpout) != 0x00);
    chipSettingsDialog.setGP2ComboBoxCurrentIndex(chipSettings_.gp2 == MCP2210::PCGPIO ? (0x04 & chipSettings_.gpdir) == 0x00 : chipSettings_.gp2 + 1);
    chipSettingsDialog.setGP2DefaultValueCheckBox((0x04 & chipSettings_.gpout) != 0x00);
    chipSettingsDialog.setGP3ComboBoxCurrentIndex(chipSettings_.gp3 == MCP2210::PCGPIO ? (0x08 & chipSettings_.gpdir) == 0x00 : chipSettings_.gp3 + 1);
    chipSettingsDialog.setGP3DefaultValueCheckBox((0x08 & chipSettings_.gpout) != 0x00);
    chipSettingsDialog.setGP4ComboBoxCurrentIndex(chipSettings_.gp4 == MCP2210::PCGPIO ? (0x10 & chipSettings_.gpdir) == 0x00 : chipSettings_.gp4 + 1);
    chipSettingsDialog.setGP4DefaultValueCheckBox((0x10 & chipSettings_.gpout) != 0x00);
    chipSettingsDialog.setGP5ComboBoxCurrentIndex(chipSettings_.gp5 == MCP2210::PCGPIO ? (0x20 & chipSettings_.gpdir) == 0x00 : chipSettings_.gp5 + 1);
    chipSettingsDialog.setGP5DefaultValueCheckBox((0x20 & chipSettings_.gpout) != 0x00);
    chipSettingsDialog.setGP6ComboBoxCurrentIndex(chipSettings_.gp6 == MCP2210::PCGPIO ? (0x40 & chipSettings_.gpdir) == 0x00 : chipSettings_.gp6 + 1);
    chipSettingsDialog.setGP6DefaultValueCheckBox((0x40 & chipSettings_.gpout) != 0x00);
    chipSettingsDialog.setGP7ComboBoxCurrentIndex(chipSettings_.gp7 == MCP2210::PCGPIO ? (0x80 & chipSettings_.gpdir) == 0x00 : chipSettings_.gp7 + 1);
    chipSettingsDialog.setGP7DefaultValueCheckBox((0x80 & chipSettings_.gpout) != 0x00);
    chipSettingsDialog.setGP8ComboBoxCurrentIndex(chipSettings_.gp8 == MCP2210::PCGPIO ? 0 : 1);
    chipSettingsDialog.setInterruptModeComboBoxCurrentIndex(chipSettings_.intmode);
    chipSettingsDialog.setRemoteWakeUpCheckBox(chipSettings_.rmwakeup);
    chipSettingsDialog.setSPIBusCaptiveCheckBox(chipSettings_.nrelspi);
    if (chipSettingsDialog.exec() == QDialog::Accepted) {  // If the user clicks "OK", the new chip settings should be applied
        MCP2210::ChipSettings chipSettings = chipSettings_;  // Local variable required to hold chip settings that may or may not be applied
        chipSettings.gp0 = static_cast<quint8>(chipSettingsDialog.gp0ComboBoxCurrentIndex() > 0 ? chipSettingsDialog.gp0ComboBoxCurrentIndex() - 1 : MCP2210::PCGPIO);
        chipSettings.gp1 = static_cast<quint8>(chipSettingsDialog.gp1ComboBoxCurrentIndex() > 0 ? chipSettingsDialog.gp1ComboBoxCurrentIndex() - 1 : MCP2210::PCGPIO);
        chipSettings.gp2 = static_cast<quint8>(chipSettingsDialog.gp2ComboBoxCurrentIndex() > 0 ? chipSettingsDialog.gp2ComboBoxCurrentIndex() - 1 : MCP2210::PCGPIO);
        chipSettings.gp3 = static_cast<quint8>(chipSettingsDialog.gp3ComboBoxCurrentIndex() > 0 ? chipSettingsDialog.gp3ComboBoxCurrentIndex() - 1 : MCP2210::PCGPIO);
        chipSettings.gp4 = static_cast<quint8>(chipSettingsDialog.gp4ComboBoxCurrentIndex() > 0 ? chipSettingsDialog.gp4ComboBoxCurrentIndex() - 1 : MCP2210::PCGPIO);
        chipSettings.gp5 = static_cast<quint8>(chipSettingsDialog.gp5ComboBoxCurrentIndex() > 0 ? chipSettingsDialog.gp5ComboBoxCurrentIndex() - 1 : MCP2210::PCGPIO);
        chipSettings.gp6 = static_cast<quint8>(chipSettingsDialog.gp6ComboBoxCurrentIndex() > 0 ? chipSettingsDialog.gp6ComboBoxCurrentIndex() - 1 : MCP2210::PCGPIO);
        chipSettings.gp7 = static_cast<quint8>(chipSettingsDialog.gp7ComboBoxCurrentIndex() > 0 ? chipSettingsDialog.gp7ComboBoxCurrentIndex() - 1 : MCP2210::PCGPIO);
        chipSettings.gp8 = static_cast<quint8>(chipSettingsDialog.gp8ComboBoxCurrentIndex() == 0 ? MCP2210::PCGPIO : MCP2210::PCFUNC);
        chipSettings.gpdir = static_cast<quint8>((chipSettingsDialog.gp7ComboBoxCurrentIndex() != 1) << 7 |  // All pins have their direction set to input by default, except those pins that are specifically set to be outputs
                                                 (chipSettingsDialog.gp6ComboBoxCurrentIndex() != 1) << 6 |
                                                 (chipSettingsDialog.gp5ComboBoxCurrentIndex() != 1) << 5 |
                                                 (chipSettingsDialog.gp4ComboBoxCurrentIndex() != 1) << 4 |
                                                 (chipSettingsDialog.gp3ComboBoxCurrentIndex() != 1) << 3 |
                                                 (chipSettingsDialog.gp2ComboBoxCurrentIndex() != 1) << 2 |
                                                 (chipSettingsDialog.gp1ComboBoxCurrentIndex() != 1) << 1 |
                                                 (chipSettingsDialog.gp0ComboBoxCurrentIndex() != 1));
        chipSettings.gpout = static_cast<quint8>(chipSettingsDialog.gp7DefaultValueCheckBoxIsChecked() << 7 |
                                                 chipSettingsDialog.gp6DefaultValueCheckBoxIsChecked() << 6 |
                                                 chipSettingsDialog.gp5DefaultValueCheckBoxIsChecked() << 5 |
                                                 chipSettingsDialog.gp4DefaultValueCheckBoxIsChecked() << 4 |
                                                 chipSettingsDialog.gp3DefaultValueCheckBoxIsChecked() << 3 |
                                                 chipSettingsDialog.gp2DefaultValueCheckBoxIsChecked() << 2 |
                                                 chipSettingsDialog.gp1DefaultValueCheckBoxIsChecked() << 1 |
                                                 chipSettingsDialog.gp0DefaultValueCheckBoxIsChecked());
        chipSettings.rmwakeup = chipSettingsDialog.remoteWakeUpCheckBoxIsChecked();
        chipSettings.intmode = static_cast<quint8>(chipSettingsDialog.interruptModeComboBoxCurrentIndex());
        chipSettings.nrelspi = chipSettingsDialog.spiBusCaptiveCheckBoxIsChecked();
        int errcnt = 0;
        QString errstr;
        mcp2210_.configureChipSettings(chipSettings, errcnt, errstr);
        if (validateOperation(tr("configure chip settings"), errcnt, errstr)) {
            chipSettings_ = chipSettings;  // Reflect new chip settings
            initializeView();  // and reinitialize device window
        }
    }
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

void DeviceWindow::on_actionResetSettings_triggered()
{
    int errcnt = 0;
    QString errstr;
    MCP2210::ChipSettings chipSettings = mcp2210_.getNVChipSettings(errcnt, errstr);
    MCP2210::SPISettings spiSettings = mcp2210_.getNVSPISettings(errcnt, errstr);
    if (validateOperation(tr("retrieve power-up settings"), errcnt, errstr)) {
        mcp2210_.configureChipSettings(chipSettings, errcnt, errstr);
        mcp2210_.configureSPISettings(spiSettings, errcnt, errstr);
        if (validateOperation(tr("reset settings"), errcnt, errstr)) {
            chipSettings_ = chipSettings;  // Reflect chip
            spiSettings_ = spiSettings;  // and SPI settings,
            initializeView();  // and then reinitialize device window
        }
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

void DeviceWindow::on_checkBoxGPIO0_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.setGPIO(MCP2210::GPIO0, ui->checkBoxGPIO0->isChecked(), errcnt, errstr);  // Set GPIO0 according to the user choice
    validateOperation(tr("switch GPIO0"), errcnt, errstr);
}

void DeviceWindow::on_checkBoxGPIO1_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.setGPIO(MCP2210::GPIO1, ui->checkBoxGPIO1->isChecked(), errcnt, errstr);  // Set GPIO1 according to the user choice
    validateOperation(tr("switch GPIO1"), errcnt, errstr);
}

void DeviceWindow::on_checkBoxGPIO2_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.setGPIO(MCP2210::GPIO2, ui->checkBoxGPIO2->isChecked(), errcnt, errstr);  // Set GPIO2 according to the user choice
    validateOperation(tr("switch GPIO2"), errcnt, errstr);
}

void DeviceWindow::on_checkBoxGPIO3_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.setGPIO(MCP2210::GPIO3, ui->checkBoxGPIO3->isChecked(), errcnt, errstr);  // Set GPIO3 according to the user choice
    validateOperation(tr("switch GPIO3"), errcnt, errstr);
}

void DeviceWindow::on_checkBoxGPIO4_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.setGPIO(MCP2210::GPIO4, ui->checkBoxGPIO4->isChecked(), errcnt, errstr);  // Set GPIO4 according to the user choice
    validateOperation(tr("switch GPIO4"), errcnt, errstr);
}

void DeviceWindow::on_checkBoxGPIO5_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.setGPIO(MCP2210::GPIO5, ui->checkBoxGPIO5->isChecked(), errcnt, errstr);  // Set GPIO5 according to the user choice
    validateOperation(tr("switch GPIO5"), errcnt, errstr);
}

void DeviceWindow::on_checkBoxGPIO6_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.setGPIO(MCP2210::GPIO6, ui->checkBoxGPIO6->isChecked(), errcnt, errstr);  // Set GPIO6 according to the user choice
    validateOperation(tr("switch GPIO6"), errcnt, errstr);
}

void DeviceWindow::on_checkBoxGPIO7_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.setGPIO(MCP2210::GPIO7, ui->checkBoxGPIO7->isChecked(), errcnt, errstr);  // Set GPIO7 according to the user choice
    validateOperation(tr("switch GPIO7"), errcnt, errstr);
}

void DeviceWindow::on_pushButtonSPIDelays_clicked()
{
    DelaysDialog delaysDialog(this);
    // TODO Setup variable and get SPI delays
    // TODO Set widget values
    if (delaysDialog.exec() == QDialog::Accepted) {  // If the user clicks "OK", the new delay settings are applied to the current channel
        // TODO Get widget values
        int errcnt = 0;
        QString errstr;
        //mcp2210_.configureSPISettings(const SPISettings &settings, errcnt, errstr);
        if (validateOperation(tr("configure spi settings"), errcnt, errstr)) {
            // Set variable value
        }
    }
}

void DeviceWindow::on_pushButtonZero_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.resetEventCounter(errcnt, errstr);
    validateOperation(tr("reset event counter"), errcnt, errstr);
}

// This is the main update routine
void DeviceWindow::update()
{
    int errcnt = 0;
    QString errstr;
    quint16 gpios = mcp2210_.getGPIOs(errcnt, errstr);
    quint16 eventCount = 0;
    if (chipSettings_.gp6 == MCP2210::PCFUNC && chipSettings_.intmode != MCP2210::IMNOCNT) {
        eventCount = mcp2210_.getEventCount(errcnt, errstr);
    }
    if (validateOperation(tr("update"), errcnt, errstr)) {  // If no errors occur
        updateView(gpios, eventCount);  // Update values
    }
}

// Partially disables device window
void DeviceWindow::disableView()
{
    ui->actionInformation->setEnabled(false);
    ui->actionStatus->setEnabled(false);
    ui->actionChipSettings->setEnabled(false);
    ui->actionClose->setText(tr("&Close Window"));
    ui->centralWidget->setEnabled(false);
    ui->statusBar->setEnabled(false);
    viewEnabled_ = false;
}

// Initializes the event counter controls
void DeviceWindow::initializeEventCounterControls()
{
    ui->groupBoxEventCounter->setEnabled(chipSettings_.gp6 == MCP2210::PCFUNC && chipSettings_.intmode != MCP2210::IMNOCNT);
    switch (chipSettings_.intmode) {
        case MCP2210::IMCNTFE:
            ui->labelCount->setText(tr("Falling edge count"));
            break;
        case MCP2210::IMCNTRE:
            ui->labelCount->setText(tr("Rising edge count"));
            break;
        case MCP2210::IMCNTLP:
            ui->labelCount->setText(tr("Low pulse count"));
            break;
        case MCP2210::IMCNTHP:
            ui->labelCount->setText(tr("High pulse count"));
            break;
        default:
            ui->labelCount->setText(tr("Count"));
    }
}

// Initializes the GPIO controls
void DeviceWindow::initializeGPIOControls()
{
    ui->checkBoxGPIO0->setEnabled(chipSettings_.gp0 == MCP2210::PCGPIO && (0x01 & chipSettings_.gpdir) == 0x00);
    ui->checkBoxGPIO1->setEnabled(chipSettings_.gp1 == MCP2210::PCGPIO && (0x02 & chipSettings_.gpdir) == 0x00);
    ui->checkBoxGPIO2->setEnabled(chipSettings_.gp2 == MCP2210::PCGPIO && (0x04 & chipSettings_.gpdir) == 0x00);
    ui->checkBoxGPIO3->setEnabled(chipSettings_.gp3 == MCP2210::PCGPIO && (0x08 & chipSettings_.gpdir) == 0x00);
    ui->checkBoxGPIO4->setEnabled(chipSettings_.gp4 == MCP2210::PCGPIO && (0x10 & chipSettings_.gpdir) == 0x00);
    ui->checkBoxGPIO5->setEnabled(chipSettings_.gp5 == MCP2210::PCGPIO && (0x20 & chipSettings_.gpdir) == 0x00);
    ui->checkBoxGPIO6->setEnabled(chipSettings_.gp6 == MCP2210::PCGPIO && (0x40 & chipSettings_.gpdir) == 0x00);
    ui->checkBoxGPIO7->setEnabled(chipSettings_.gp7 == MCP2210::PCGPIO && (0x80 & chipSettings_.gpdir) == 0x00);
}

// Initializes the SPI controls
void DeviceWindow::initializeSPIControls()
{
    QStringList channelList;
    if (chipSettings_.gp0 == MCP2210::PCCS) {
        channelList += "0";
    }
    if (chipSettings_.gp1 == MCP2210::PCCS) {
        channelList += "1";
    }
    if (chipSettings_.gp2 == MCP2210::PCCS) {
        channelList += "2";
    }
    if (chipSettings_.gp3 == MCP2210::PCCS) {
        channelList += "3";
    }
    if (chipSettings_.gp4 == MCP2210::PCCS) {
        channelList += "4";
    }
    if (chipSettings_.gp5 == MCP2210::PCCS) {
        channelList += "5";
    }
    if (chipSettings_.gp6 == MCP2210::PCCS) {
        channelList += "6";
    }
    if (chipSettings_.gp7 == MCP2210::PCCS) {
        channelList += "7";
    }
    bool spiEnabled = !channelList.isEmpty();
    ui->groupBoxSPIConfiguration->setEnabled(spiEnabled);
    ui->groupBoxSPITransfers->setEnabled(spiEnabled);
    ui->comboBoxChannel->clear();
    ui->comboBoxChannel->addItems(channelList);
}

// This is the routine that is used to initialize (or reinitialize) the device window
void DeviceWindow::initializeView()
{
    initializeGPIOControls();
    initializeEventCounterControls();
    initializeSPIControls();
    viewEnabled_ = true;
}

// Reads settings from the MCP2210 volatile memory area
void DeviceWindow::readSettings()
{
    int errcnt = 0;
    QString errstr;
    chipSettings_ = mcp2210_.getChipSettings(errcnt, errstr);
    spiSettings_ = mcp2210_.getSPISettings(errcnt, errstr);
    if (errcnt > 0) {
        this->hide();  // Hide the window, if applicable, to let the user know that the device is practically closed
        mcp2210_.close();
        if (mcp2210_.disconnected()) {
            QMessageBox::critical(this, tr("Error"), tr("Device disconnected.\n\nPlease reconnect it and try again."));
        } else {
            errstr.chop(1);  // Remove the last character, which is always a newline
            QMessageBox::critical(this, tr("Error"), tr("Failed to read device settings. The operation returned the following error(s):\n– %1\n\nPlease try accessing the device again.", "", errcnt).arg(errstr.replace("\n", "\n– ")));
        }
        this->deleteLater();  // This is a severe error that requires the window to be closed, because the state of the device is not known, and therefore it is not safe to proceed
    }
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
            QMessageBox::critical(this, tr("Error"), tr("Failed to %1. The operation returned the following error(s):\n– %2", "", errcnt).arg(operation, errstr.replace("\n", "\n– ")));
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

// Updates the view
void DeviceWindow::updateView(quint16 gpios, quint16 eventCount)
{
    ui->checkBoxGPIO0->setChecked((0x0001 & gpios) != 0x0000);
    ui->checkBoxGPIO1->setChecked((0x0002 & gpios) != 0x0000);
    ui->checkBoxGPIO2->setChecked((0x0004 & gpios) != 0x0000);
    ui->checkBoxGPIO3->setChecked((0x0008 & gpios) != 0x0000);
    ui->checkBoxGPIO4->setChecked((0x0010 & gpios) != 0x0000);
    ui->checkBoxGPIO5->setChecked((0x0020 & gpios) != 0x0000);
    ui->checkBoxGPIO6->setChecked((0x0040 & gpios) != 0x0000);
    ui->checkBoxGPIO7->setChecked((0x0080 & gpios) != 0x0000);
    ui->checkBoxGPIO8->setChecked((0x0100 & gpios) != 0x0000);
    ui->lcdNumberCount->display(eventCount);
}
