/* MCP2210 Commander - Version 1.0.2 for Debian Linux
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


#ifndef CSSETTINGSDIALOG_H
#define CSSETTINGSDIALOG_H

// Includes
#include <QDialog>

namespace Ui {
class CSSettingsDialog;
}

class CSSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSSettingsDialog(QWidget *parent = nullptr);
    ~CSSettingsDialog();

    bool activeCS0CheckBoxIsChecked();
    bool activeCS1CheckBoxIsChecked();
    bool activeCS2CheckBoxIsChecked();
    bool activeCS3CheckBoxIsChecked();
    bool activeCS4CheckBoxIsChecked();
    bool activeCS5CheckBoxIsChecked();
    bool activeCS6CheckBoxIsChecked();
    bool activeCS7CheckBoxIsChecked();
    bool idleCS0CheckBoxIsChecked();
    bool idleCS1CheckBoxIsChecked();
    bool idleCS2CheckBoxIsChecked();
    bool idleCS3CheckBoxIsChecked();
    bool idleCS4CheckBoxIsChecked();
    bool idleCS5CheckBoxIsChecked();
    bool idleCS6CheckBoxIsChecked();
    bool idleCS7CheckBoxIsChecked();
    void setActiveCS0CheckBox(bool cs0ActiveLevel);
    void setActiveCS1CheckBox(bool cs1ActiveLevel);
    void setActiveCS2CheckBox(bool cs2ActiveLevel);
    void setActiveCS3CheckBox(bool cs3ActiveLevel);
    void setActiveCS4CheckBox(bool cs4ActiveLevel);
    void setActiveCS5CheckBox(bool cs5ActiveLevel);
    void setActiveCS6CheckBox(bool cs6ActiveLevel);
    void setActiveCS7CheckBox(bool cs7ActiveLevel);
    void setIdleCS0CheckBox(bool cs0IdleLevel);
    void setIdleCS1CheckBox(bool cs1IdleLevel);
    void setIdleCS2CheckBox(bool cs2IdleLevel);
    void setIdleCS3CheckBox(bool cs3IdleLevel);
    void setIdleCS4CheckBox(bool cs4IdleLevel);
    void setIdleCS5CheckBox(bool cs5IdleLevel);
    void setIdleCS6CheckBox(bool cs6IdleLevel);
    void setIdleCS7CheckBox(bool cs7IdleLevel);

private:
    Ui::CSSettingsDialog *ui;
};

#endif  // CSSETTINGSDIALOG_H
