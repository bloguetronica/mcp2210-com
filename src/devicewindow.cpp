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
#include <QClipboard>
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QGuiApplication>
#include <QMessageBox>
#include <QProgressDialog>
#include <QRegExp>
#include <QRegExpValidator>
#include <QStringList>
#include "common.h"
#include "chipsettingsdialog.h"
#include "cssettingsdialog.h"
#include "delaysdialog.h"
#include "devicewindow.h"
#include "ui_devicewindow.h"

// Definitions
const int CENTRAL_HEIGHT = 491;
const int ERR_LIMIT = 10;

// The following values are applicable to applySPISettings()
const bool CSSINGLE = true;   // Enforce CS settings for one channel only
const bool CSCUSTOM = false;  // Allow custom configuration and possibly multiple active low CS pins
const bool BRTGET = true;     // Get nearest compatible bit rate
const bool BRTKEEP = false;   // Keep current bit rate

DeviceWindow::DeviceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeviceWindow)
{
    ui->setupUi(this);
    ui->lineEditWrite->setValidator(new QRegExpValidator(QRegExp("[A-Fa-f\\d\\s]+"), this));  // Spaces are also allowed
    labelStatus_ = new QLabel(this);
    this->statusBar()->addWidget(labelStatus_);
    timer_ = new QTimer(this);
    connect(QGuiApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(updatePushButtonClipboardPasteWrite()));
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
    this->setFixedHeight(ui->menuBar->height() + CENTRAL_HEIGHT + ui->statusBar->height());
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
        MCP2210::ChipSettings chipSettings = chipSettings_;  // Local variable required in order to hold chip settings that may or may not be applied
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
        chipSettings = mcp2210_.getChipSettings(errcnt, errstr);  // Although not strictly necessary, it is a good practice to read back the applied settings in this case
        if (validateOperation(tr("apply chip settings"), errcnt, errstr)) {
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
        chipSettings = mcp2210_.getChipSettings(errcnt, errstr);  // Although not strictly necessary,
        spiSettings = mcp2210_.getSPISettings(errcnt, errstr);  // it is advisable to read back all the previously applied settings
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
            statusDialog_->setAttribute(Qt::WA_DeleteOnClose);  // It is important to delete the dialog in memory once closed, in order to force the application to retrieve the device status if the window is opened again
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

void DeviceWindow::on_comboBoxChannel_activated()
{
    applySPISettings(CSSINGLE, BRTKEEP);
}

void DeviceWindow::on_doubleSpinBoxBitRate_editingFinished()
{
    applySPISettings(CSCUSTOM, BRTGET);
}

void DeviceWindow::on_lineEditRead_textChanged(const QString &text)
{
    ui->pushButtonClipboardCopyRead->setEnabled(!text.isEmpty());
}

void DeviceWindow::on_lineEditWrite_editingFinished()
{
    ui->lineEditWrite->setText(write_.toHexadecimal());  // Required to reformat the hexadecimal string
    applySPISettings(CSCUSTOM, BRTKEEP);
}

void DeviceWindow::on_lineEditWrite_textChanged(const QString &text)
{
    ui->pushButtonClipboardCopyWrite->setEnabled(!text.isEmpty());
    write_.fromHexadecimal(text);  // This also forces a retrim whenever on_lineEditWrite_editingFinished() is triggered, which is useful case the reformatted hexadecimal string does not fit the line edit box (required in order to follow the WYSIWYG principle)
    ui->pushButtonTransfer->setEnabled(write_.vector.size() != 0);  // The button "Transfer" is enabled if the string is valid, that is, its conversion leads to a non-empty QVector
}

void DeviceWindow::on_lineEditWrite_textEdited(const QString &text)
{
    int curPosition = ui->lineEditWrite->cursorPosition();
    ui->lineEditWrite->setText(text.toLower());
    ui->lineEditWrite->setCursorPosition(curPosition);
}

void DeviceWindow::on_pushButtonClipboardCopyRead_clicked()
{
    QGuiApplication::clipboard()->setText(ui->lineEditRead->text());
}

void DeviceWindow::on_pushButtonClipboardCopyWrite_clicked()
{
    QGuiApplication::clipboard()->setText(ui->lineEditWrite->text());
}

void DeviceWindow::on_pushButtonClipboardPasteWrite_clicked()
{
    ui->lineEditWrite->setText(QGuiApplication::clipboard()->text().toLower());  // No need to filter the clipboard contents
    ui->lineEditWrite->setFocus();  // This ensures that on_lineEditWrite_editingFinished() is triggered once the user clicks elsewhere
}

void DeviceWindow::on_pushButtonCSSettings_clicked()
{
    CSSettingsDialog csSettingsDialog(this);
    csSettingsDialog.setActiveCS0CheckBox((0x01 & spiSettings_.actcs) != 0x00);
    csSettingsDialog.setActiveCS1CheckBox((0x02 & spiSettings_.actcs) != 0x00);
    csSettingsDialog.setActiveCS2CheckBox((0x04 & spiSettings_.actcs) != 0x00);
    csSettingsDialog.setActiveCS3CheckBox((0x08 & spiSettings_.actcs) != 0x00);
    csSettingsDialog.setActiveCS4CheckBox((0x10 & spiSettings_.actcs) != 0x00);
    csSettingsDialog.setActiveCS5CheckBox((0x20 & spiSettings_.actcs) != 0x00);
    csSettingsDialog.setActiveCS6CheckBox((0x40 & spiSettings_.actcs) != 0x00);
    csSettingsDialog.setActiveCS7CheckBox((0x80 & spiSettings_.actcs) != 0x00);
    csSettingsDialog.setIdleCS0CheckBox((0x01 & spiSettings_.idlcs) != 0x00);
    csSettingsDialog.setIdleCS1CheckBox((0x02 & spiSettings_.idlcs) != 0x00);
    csSettingsDialog.setIdleCS2CheckBox((0x04 & spiSettings_.idlcs) != 0x00);
    csSettingsDialog.setIdleCS3CheckBox((0x08 & spiSettings_.idlcs) != 0x00);
    csSettingsDialog.setIdleCS4CheckBox((0x10 & spiSettings_.idlcs) != 0x00);
    csSettingsDialog.setIdleCS5CheckBox((0x20 & spiSettings_.idlcs) != 0x00);
    csSettingsDialog.setIdleCS6CheckBox((0x40 & spiSettings_.idlcs) != 0x00);
    csSettingsDialog.setIdleCS7CheckBox((0x80 & spiSettings_.idlcs) != 0x00);
    if (csSettingsDialog.exec() == QDialog::Accepted) {
        MCP2210::SPISettings spiSettings = spiSettings_;  // Local variable required in order to hold SPI settings that may or may not be applied
        spiSettings.actcs = static_cast<quint8>(csSettingsDialog.activeCS7CheckBoxIsChecked() << 7 |
                                                csSettingsDialog.activeCS6CheckBoxIsChecked() << 6 |
                                                csSettingsDialog.activeCS5CheckBoxIsChecked() << 5 |
                                                csSettingsDialog.activeCS4CheckBoxIsChecked() << 4 |
                                                csSettingsDialog.activeCS3CheckBoxIsChecked() << 3 |
                                                csSettingsDialog.activeCS2CheckBoxIsChecked() << 2 |
                                                csSettingsDialog.activeCS1CheckBoxIsChecked() << 1 |
                                                csSettingsDialog.activeCS0CheckBoxIsChecked());
        spiSettings.idlcs = static_cast<quint8>(csSettingsDialog.idleCS7CheckBoxIsChecked() << 7 |
                                                csSettingsDialog.idleCS6CheckBoxIsChecked() << 6 |
                                                csSettingsDialog.idleCS5CheckBoxIsChecked() << 5 |
                                                csSettingsDialog.idleCS4CheckBoxIsChecked() << 4 |
                                                csSettingsDialog.idleCS3CheckBoxIsChecked() << 3 |
                                                csSettingsDialog.idleCS2CheckBoxIsChecked() << 2 |
                                                csSettingsDialog.idleCS1CheckBoxIsChecked() << 1 |
                                                csSettingsDialog.idleCS0CheckBoxIsChecked());
        int errcnt = 0;
        QString errstr;
        mcp2210_.configureSPISettings(spiSettings, errcnt, errstr);
        spiSettings = mcp2210_.getSPISettings(errcnt, errstr);  // Although not strictly necessary, it is a good practice to read back the applied settings in this case
        if (validateOperation(tr("apply chip select settings"), errcnt, errstr)) {
            spiSettings_ = spiSettings;  // Reflect new SPI settings
            initializeView();  // and reinitialize device window
        }
    }
}

void DeviceWindow::on_pushButtonSPIDelays_clicked()
{
    DelaysDialog delaysDialog(this);
    delaysDialog.setCSToDataDelaySpinBoxValue(spiSettings_.csdtdly);
    delaysDialog.setDataToCSDelaySpinBoxValue(spiSettings_.dtcsdly);
    delaysDialog.setInterByteDelaySpinBoxValue(spiSettings_.itbytdly);
    if (delaysDialog.exec() == QDialog::Accepted) {
        MCP2210::SPISettings spiSettings = spiSettings_;  // Local variable required in order to hold SPI settings that may or may not be applied
        spiSettings.csdtdly = delaysDialog.csToDataDelaySpinBoxValue();
        spiSettings.dtcsdly = delaysDialog.dataToCSDelaySpinBoxValue();
        spiSettings.itbytdly = delaysDialog.interByteDelaySpinBoxValue();
        int errcnt = 0;
        QString errstr;
        mcp2210_.configureSPISettings(spiSettings, errcnt, errstr);
        spiSettings = mcp2210_.getSPISettings(errcnt, errstr);  // Although not strictly necessary, it is a good practice to read back the applied settings in this case
        if (validateOperation(tr("apply SPI delays"), errcnt, errstr)) {
            spiSettings_ = spiSettings;  // Reflect new SPI settings
            initializeView();  // and reinitialize device window
        }
    }
}

void DeviceWindow::on_pushButtonTransfer_clicked()
{
    size_t bytesToTransfer = write_.vector.size();
    size_t bytesProcessed = 0;
    QProgressDialog spiTransferProgress("", tr("Abort"), 0, static_cast<int>(bytesToTransfer), this);
    spiTransferProgress.setWindowTitle(tr("SPI transfer"));
    spiTransferProgress.setWindowModality(Qt::WindowModal);
    spiTransferProgress.setMinimumDuration(0);  // Because QCoreApplication::processEvents() is called, the progress dialog needs be displayed right away
    Data read;
    timer_->stop();  // The update timer should be stopped during SPI transfers
    QElapsedTimer time;
    time.start();
    int errcnt = 0;
    QString errstr;
    mcp2210_.cancelSPITransfer(errcnt, errstr);  // Just as a precautionary measure to force a start from scratch
    quint8 spiTransferStatus = MCP2210::TRANSFER_STARTED;
    while (bytesProcessed < bytesToTransfer) {  // For future reference, the variable "spiTransferStatus" does not provide a reliable way to check if the transfer is actually completed (e.g., by evaluating "spiTransferStatus != MCP2210::TRANSFER_FINISHED"), and relying on that variable alone may even lead to a crash!
        if (spiTransferProgress.wasCanceled()) {  // If the user clicks "Abort"
            mcp2210_.cancelSPITransfer(errcnt, errstr);  // This ensures a clean slate for any process that follows
            break;  // Abort the SPI transfer operation
        }
        size_t bytesRemaining = bytesToTransfer - bytesProcessed;
        size_t fragmentSize = bytesRemaining > MCP2210::SPIDATA_MAXSIZE ? MCP2210::SPIDATA_MAXSIZE : bytesRemaining;
        QVector<quint8> readFragment = mcp2210_.spiTransfer(write_.fragment(bytesProcessed, fragmentSize), spiTransferStatus, errcnt, errstr);  // Transfer SPI data
        if (errcnt > 0) {  // In case of error
            spiTransferProgress.cancel();  // Important!
            break;  // Abort the SPI transfer operation
        }
        if (spiTransferStatus == MCP2210::BUSY) {  // The bus is in use by another SPI master
            spiTransferProgress.setLabelText(tr("Waiting for the SPI bus to be released..."));
        } else {
            spiTransferProgress.setLabelText(tr("Performing SPI transfer..."));
            if (spiTransferStatus == MCP2210::TRANSFER_NOT_FINISHED || spiTransferStatus == MCP2210::TRANSFER_FINISHED) {
                read.vector += readFragment;  // The returned fragment could be considered valid at this point
                bytesProcessed += fragmentSize;
            }
        }
        spiTransferProgress.setValue(static_cast<int>(bytesProcessed));  // Note that this should be done here at the end of the loop, outside the previous if statements
        QCoreApplication::processEvents();  // Required in order to maintain responsiveness
    }
    qint64 elapsedTime = time.elapsed();  // Elapsed time in milliseconds
    timer_->start();  // Restart the timer
    ui->lineEditRead->setText(read.toHexadecimal());  // At least, a partial result should be shown if an error occurs
    if (errcnt > 0) {  // Update status bar
        labelStatus_->setText(tr("SPI transfer failed."));
    } else if (spiTransferProgress.wasCanceled()){
        labelStatus_->setText(tr("SPI transfer aborted by the user."));
    } else if (elapsedTime < 1000) {
        labelStatus_->setText(tr("SPI transfer completed. %1 bytes transferred in %2 ms.").arg(2 * bytesProcessed).arg(elapsedTime));
    } else {
        labelStatus_->setText(tr("SPI transfer completed. %1 bytes transferred in %2 s.").arg(2 * bytesProcessed).arg(locale_.toString(elapsedTime / 1000.0, 'f', 3)));
    }
    validateOperation(tr("transfer SPI data"), errcnt, errstr);
}

void DeviceWindow::on_pushButtonZero_clicked()
{
    int errcnt = 0;
    QString errstr;
    mcp2210_.resetEventCounter(errcnt, errstr);
    validateOperation(tr("reset event counter"), errcnt, errstr);
}

void DeviceWindow::on_spinBoxCPHA_editingFinished()
{
    applySPISettings(CSCUSTOM, BRTKEEP);
}

void DeviceWindow::on_spinBoxCPHA_valueChanged(int i)
{
    ui->spinBoxMode->setValue(2 * ui->spinBoxCPOL->value() + i);
}

void DeviceWindow::on_spinBoxCPOL_editingFinished()
{
    applySPISettings(CSCUSTOM, BRTKEEP);
}

void DeviceWindow::on_spinBoxCPOL_valueChanged(int i)
{
    ui->spinBoxMode->setValue(2 * i + ui->spinBoxCPHA->value());
}

void DeviceWindow::on_spinBoxMode_editingFinished()
{
    applySPISettings(CSCUSTOM, BRTKEEP);
}

void DeviceWindow::on_spinBoxMode_valueChanged(int i)
{
    ui->spinBoxCPOL->setValue(i / 2);
    ui->spinBoxCPHA->setValue(i % 2);
}

// This is the main update routine
void DeviceWindow::update()
{
    int errcnt = 0;
    QString errstr;
    quint16 gpios = mcp2210_.getGPIOs(errcnt, errstr);
    quint16 eventCount = 0;
    if (chipSettings_.gp6 == MCP2210::PCFUNC && chipSettings_.intmode != MCP2210::IMNOCNT) {  // This will save overhead during updates, because the MCP2210 will not count events and its counter will default to zero unless both conditions are satisfied
        eventCount = mcp2210_.getEventCount(errcnt, errstr);
    }
    if (validateOperation(tr("update"), errcnt, errstr)) {  // If no errors occur
        updateView(gpios, eventCount);  // Update values
    }
}

// This is executed when the clipboard contents change
void DeviceWindow::updatePushButtonClipboardPasteWrite()
{
    ui->pushButtonClipboardPasteWrite->setEnabled(isClipboardTextValid());
}

// Applies the SPI settings defined by the user
void DeviceWindow::applySPISettings(bool enforceSingleChannel, bool getCompatibleBitrate)
{
    MCP2210::SPISettings spiSettings = spiSettings_;  // Local variable required in order to hold SPI settings that may or may not be applied;
    spiSettings.nbytes = write_.vector.size();
    spiSettings.mode = static_cast<quint8>(ui->spinBoxMode->value());
    if (enforceSingleChannel && ui->comboBoxChannel->currentIndex() != 0) {  // If the current index of comboBoxChannel is zero, then no specific channel is selected and no changes should be applied
        spiSettings.actcs = static_cast<quint8>(~(0x0001 << ui->comboBoxChannel->currentText().toUInt()));  // The CS pin that corresponds to the selected channel is active low
        spiSettings.idlcs = 0xff;  // All CS pins should idle high by default
    }
    int errcnt = 0;
    QString errstr;
    if (getCompatibleBitrate) {
        quint32 intendedBitrate = static_cast<quint32>(1000 * ui->doubleSpinBoxBitRate->value());
        quint32 testBitrate = static_cast<quint32>(1.5 * intendedBitrate);  // Variable used for testing and finding compatible bit rates (multiplier value was determined empirically)
        quint32 nearestLowerBitrate = MCP2210::BRT1K464, nearestUpperBitrate = MCP2210::BRT12M;  // These variables are assigned here, not just for correctness, but to allow algorithmic simplification
        while (errcnt == 0) {
            spiSettings.bitrate = testBitrate;
            mcp2210_.configureSPISettings(spiSettings, errcnt, errstr);
            quint32 returnedBitrate = mcp2210_.getSPISettings(errcnt, errstr).bitrate;
            if (returnedBitrate == testBitrate) {
                if (testBitrate >= intendedBitrate) {
                    nearestUpperBitrate = testBitrate;  // Can be equal to the intended value, if the latter is found to be a compatible bit rate
                }
                if (testBitrate <= intendedBitrate) {
                    nearestLowerBitrate = testBitrate;  // Again, can be equal to the intended value, if the latter is found to be a compatible bit rate
                    break;
                }
                --testBitrate;
            } else {  // Incidentally, "returnedBitrate" is expected to be less than "testBitrate"
                testBitrate = returnedBitrate;
            }
        }
        if (nearestUpperBitrate - intendedBitrate > intendedBitrate - nearestLowerBitrate) {  // Half-way cases are approximated to the nearest upper bit rate
            spiSettings.bitrate = nearestLowerBitrate;
        } else {
            spiSettings.bitrate = nearestUpperBitrate;
        }
    }
    mcp2210_.configureSPISettings(spiSettings, errcnt, errstr);
    spiSettings = mcp2210_.getSPISettings(errcnt, errstr);  // Although not strictly necessary, it is a good practice to read back the applied settings in this case
    if (validateOperation(tr("apply SPI settings"), errcnt, errstr)) {
        spiSettings_ = spiSettings;  // Reflect new SPI settings
        initializeView();  // and reinitialize device window
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
    ui->groupBoxEventCounter->setEnabled(chipSettings_.gp6 == MCP2210::PCFUNC && chipSettings_.intmode != MCP2210::IMNOCNT);
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
    ui->comboBoxChannel->clear();
    ui->comboBoxChannel->addItem("*");
    ui->comboBoxChannel->addItems(channelList);
    if (spiSettings_.idlcs == 0xff) {
        switch (spiSettings_.actcs) {
            case 0xfe:
                ui->comboBoxChannel->setCurrentText("0");
                break;
            case 0xfd:
                ui->comboBoxChannel->setCurrentText("1");
                break;
            case 0xfb:
                ui->comboBoxChannel->setCurrentText("2");
                break;
            case 0xf7:
                ui->comboBoxChannel->setCurrentText("3");
                break;
            case 0xef:
                ui->comboBoxChannel->setCurrentText("4");
                break;
            case 0xdf:
                ui->comboBoxChannel->setCurrentText("5");
                break;
            case 0xbf:
                ui->comboBoxChannel->setCurrentText("6");
                break;
            case 0x7f:
                ui->comboBoxChannel->setCurrentText("7");
                break;
        }
    }
    ui->doubleSpinBoxBitRate->setValue(spiSettings_.bitrate / 1000.0);
    ui->spinBoxMode->setValue(spiSettings_.mode);
    bool spiEnabled = !channelList.isEmpty();
    ui->groupBoxSPIConfiguration->setEnabled(spiEnabled);
    ui->groupBoxSPITransfers->setEnabled(spiEnabled);
    ui->pushButtonClipboardPasteWrite->setEnabled(isClipboardTextValid());
}

// This is the routine that is used to initialize (or reinitialize) the device window
void DeviceWindow::initializeView()
{
    initializeGPIOControls();
    initializeEventCounterControls();
    initializeSPIControls();
    viewEnabled_ = true;
}

// Returns true if the clipboard text contains a valid hexadecimal string
bool DeviceWindow::isClipboardTextValid()
{
    QString clipboardText = QGuiApplication::clipboard()->text();
    int pos = 0;
    return QRegExpValidator(QRegExp("[A-Fa-f\\d\\s]+")).validate(clipboardText, pos) == QValidator::Acceptable;
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
