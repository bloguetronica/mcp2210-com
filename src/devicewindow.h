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


#ifndef DEVICEWINDOW_H
#define DEVICEWINDOW_H

// Includes
#include <QLabel>
#include <QMainWindow>
#include <QPointer>
#include <QResizeEvent>
#include <QString>
#include <QTimer>
#include "data.h"
#include "informationdialog.h"
#include "mcp2210.h"
#include "statusdialog.h"

namespace Ui {
class DeviceWindow;
}

class DeviceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceWindow(QWidget *parent = nullptr);
    ~DeviceWindow();

    bool isViewEnabled();
    void openDevice(quint16 vid, quint16 pid, const QString &serialString);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionAbout_triggered();
    void on_actionInformation_triggered();
    void on_actionChipSettings_triggered();
    void on_actionResetSettings_triggered();
    void on_actionStatus_triggered();
    void on_checkBoxGPIO0_clicked();
    void on_checkBoxGPIO1_clicked();
    void on_checkBoxGPIO2_clicked();
    void on_checkBoxGPIO3_clicked();
    void on_checkBoxGPIO4_clicked();
    void on_checkBoxGPIO5_clicked();
    void on_checkBoxGPIO6_clicked();
    void on_checkBoxGPIO7_clicked();
    void on_comboBoxChannel_activated();
    void on_doubleSpinBoxBitRate_editingFinished();
    void on_lineEditRead_textChanged(const QString &text);
    void on_lineEditWrite_editingFinished();
    void on_lineEditWrite_textChanged(const QString &text);
    void on_lineEditWrite_textEdited(const QString &text);
    void on_pushButtonClipboardCopyRead_clicked();
    void on_pushButtonClipboardCopyWrite_clicked();
    void on_pushButtonClipboardPasteWrite_clicked();
    void on_pushButtonCSSettings_clicked();
    void on_pushButtonSPIDelays_clicked();
    void on_pushButtonZero_clicked();
    void on_spinBoxCPHA_editingFinished();
    void on_spinBoxCPHA_valueChanged(int i);
    void on_spinBoxCPOL_editingFinished();
    void on_spinBoxCPOL_valueChanged(int i);
    void on_spinBoxMode_editingFinished();
    void on_spinBoxMode_valueChanged(int i);
    void update();
    void updatePushButtonClipboardPasteWrite();

private:
    Ui::DeviceWindow *ui;
    Data write_;
    MCP2210 mcp2210_;
    MCP2210::ChipSettings chipSettings_;
    MCP2210::SPISettings spiSettings_;
    QLabel *labelStatus_;
    QPointer<InformationDialog> informationDialog_;
    QPointer<StatusDialog> statusDialog_;
    QString serialString_;
    QTimer *timer_;
    quint16 pid_, vid_;
    bool viewEnabled_ = false;
    int erracc_ = 0;

    void applySPISettings(bool enforceSingleChannel, bool getCompatibleBitrate);
    void disableView();
    void initializeEventCounterControls();
    void initializeGPIOControls();
    void initializeSPIControls();
    void initializeView();
    bool isClipboardTextValid();
    void readSettings();
    bool validateOperation(const QString &operation, int errcnt, QString errstr);
    void updateView(quint16 gpios, quint16 eventCount);
};

#endif  // DEVICEWINDOW_H
