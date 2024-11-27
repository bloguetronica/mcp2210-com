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


#ifndef PINSDIALOG_H
#define PINSDIALOG_H

// Includes
#include <QDialog>

namespace Ui {
class PinsDialog;
}

class PinsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PinsDialog(QWidget *parent = nullptr);
    ~PinsDialog();

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
    void setGP0ComboBoxCurrentIndex(int index);
    void setGP0DefaultValueCheckBox(bool state);
    void setGP1ComboBoxCurrentIndex(int index);
    void setGP1DefaultValueCheckBox(bool state);
    void setGP2ComboBoxCurrentIndex(int index);
    void setGP2DefaultValueCheckBox(bool state);
    void setGP3ComboBoxCurrentIndex(int index);
    void setGP3DefaultValueCheckBox(bool state);
    void setGP4ComboBoxCurrentIndex(int index);
    void setGP4DefaultValueCheckBox(bool state);
    void setGP5ComboBoxCurrentIndex(int index);
    void setGP5DefaultValueCheckBox(bool state);
    void setGP6ComboBoxCurrentIndex(int index);
    void setGP6DefaultValueCheckBox(bool state);
    void setGP7ComboBoxCurrentIndex(int index);
    void setGP7DefaultValueCheckBox(bool state);
    void setGP8ComboBoxCurrentIndex(int index);

private:
    Ui::PinsDialog *ui;
};

#endif  // PINSDIALOG_H
