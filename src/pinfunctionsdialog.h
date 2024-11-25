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


#ifndef PINFUNCTIONSDIALOG_H
#define PINFUNCTIONSDIALOG_H

// Includes
#include <QDialog>

namespace Ui {
class PinFunctionsDialog;
}

class PinFunctionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PinFunctionsDialog(QWidget *parent = nullptr);
    ~PinFunctionsDialog();

    int gp0ComboBoxCurrentIndex();
    int gp1ComboBoxCurrentIndex();
    int gp2ComboBoxCurrentIndex();
    int gp3ComboBoxCurrentIndex();
    int gp4ComboBoxCurrentIndex();
    int gp5ComboBoxCurrentIndex();
    int gp6ComboBoxCurrentIndex();
    int gp7ComboBoxCurrentIndex();
    int gp8ComboBoxCurrentIndex();
    void setGP0ComboBoxCurrentIndex(int index);
    void setGP1ComboBoxCurrentIndex(int index);
    void setGP2ComboBoxCurrentIndex(int index);
    void setGP3ComboBoxCurrentIndex(int index);
    void setGP4ComboBoxCurrentIndex(int index);
    void setGP5ComboBoxCurrentIndex(int index);
    void setGP6ComboBoxCurrentIndex(int index);
    void setGP7ComboBoxCurrentIndex(int index);
    void setGP8ComboBoxCurrentIndex(int index);

private:
    Ui::PinFunctionsDialog *ui;
};

#endif  // PINFUNCTIONSDIALOG_H
