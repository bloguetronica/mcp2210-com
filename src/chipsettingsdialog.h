/* MCP2210 Commander - Version 1.0.1 for Debian Linux
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


#ifndef CHIPSETTINGSDIALOG_H
#define CHIPSETTINGSDIALOG_H

// Includes
#include <QDialog>

namespace Ui {
class ChipSettingsDialog;
}

class ChipSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChipSettingsDialog(QWidget *parent = nullptr);
    ~ChipSettingsDialog();

    int gp0ComboBoxCurrentIndex();
    bool gp0DefaultValueCheckBoxIsChecked();
    int gp1ComboBoxCurrentIndex();
    bool gp1DefaultValueCheckBoxIsChecked();
    int gp2ComboBoxCurrentIndex();
    bool gp2DefaultValueCheckBoxIsChecked();
    int gp3ComboBoxCurrentIndex();
    bool gp3DefaultValueCheckBoxIsChecked();
    int gp4ComboBoxCurrentIndex();
    bool gp4DefaultValueCheckBoxIsChecked();
    int gp5ComboBoxCurrentIndex();
    bool gp5DefaultValueCheckBoxIsChecked();
    int gp6ComboBoxCurrentIndex();
    bool gp6DefaultValueCheckBoxIsChecked();
    int gp7ComboBoxCurrentIndex();
    bool gp7DefaultValueCheckBoxIsChecked();
    int gp8ComboBoxCurrentIndex();
    int interruptModeComboBoxCurrentIndex();
    bool remoteWakeUpCheckBoxIsChecked();
    void setGP0ComboBoxCurrentIndex(int gp0ModeIndex);
    void setGP0DefaultValueCheckBox(bool gp0OutputLevel);
    void setGP1ComboBoxCurrentIndex(int gp1ModeIndex);
    void setGP1DefaultValueCheckBox(bool gp1OutputLevel);
    void setGP2ComboBoxCurrentIndex(int gp2ModeIndex);
    void setGP2DefaultValueCheckBox(bool gp2OutputLevel);
    void setGP3ComboBoxCurrentIndex(int gp3ModeIndex);
    void setGP3DefaultValueCheckBox(bool gp3OutputLevel);
    void setGP4ComboBoxCurrentIndex(int gp4ModeIndex);
    void setGP4DefaultValueCheckBox(bool gp4OutputLevel);
    void setGP5ComboBoxCurrentIndex(int gp5ModeIndex);
    void setGP5DefaultValueCheckBox(bool gp5OutputLevel);
    void setGP6ComboBoxCurrentIndex(int gp6ModeIndex);
    void setGP6DefaultValueCheckBox(bool gp6OutputLevel);
    void setGP7ComboBoxCurrentIndex(int gp7ModeIndex);
    void setGP7DefaultValueCheckBox(bool gp7OutputLevel);
    void setGP8ComboBoxCurrentIndex(int gp8ModeIndex);
    void setInterruptModeComboBoxCurrentIndex(int interruptModeIndex);
    void setRemoteWakeUpCheckBox(bool remoteWakeUp);
    void setSPIBusCaptiveCheckBox(bool spiBusCaptive);
    bool spiBusCaptiveCheckBoxIsChecked();

private:
    Ui::ChipSettingsDialog *ui;
};

#endif  // CHIPSETTINGSDIALOG_H
