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
#include "pinfunctionsdialog.h"
#include "ui_pinfunctionsdialog.h"

PinFunctionsDialog::PinFunctionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinFunctionsDialog)
{
    ui->setupUi(this);
}

PinFunctionsDialog::~PinFunctionsDialog()
{
    delete ui;
}

// Returns the current index of "comboBoxGP0"
int PinFunctionsDialog::gp0ComboBoxCurrentIndex()
{
    return ui->comboBoxGP0->currentIndex();
}

// Returns the current index of "comboBoxGP1"
int PinFunctionsDialog::gp1ComboBoxCurrentIndex()
{
    return ui->comboBoxGP1->currentIndex();
}

// Returns the current index of "comboBoxGP2"
int PinFunctionsDialog::gp2ComboBoxCurrentIndex()
{
    return ui->comboBoxGP2->currentIndex();
}

// Returns the current index of "comboBoxGP3"
int PinFunctionsDialog::gp3ComboBoxCurrentIndex()
{
    return ui->comboBoxGP3->currentIndex();
}

// Returns the current index of "comboBoxGP4"
int PinFunctionsDialog::gp4ComboBoxCurrentIndex()
{
    return ui->comboBoxGP4->currentIndex();
}

// Returns the current index of "comboBoxGP5"
int PinFunctionsDialog::gp5ComboBoxCurrentIndex()
{
    return ui->comboBoxGP5->currentIndex();
}

// Returns the current index of "comboBoxGP6"
int PinFunctionsDialog::gp6ComboBoxCurrentIndex()
{
    return ui->comboBoxGP6->currentIndex();
}

// Returns the current index of "comboBoxGP7"
int PinFunctionsDialog::gp7ComboBoxCurrentIndex()
{
    return ui->comboBoxGP7->currentIndex();
}

// Returns the current index of "comboBoxGP8"
int PinFunctionsDialog::gp8ComboBoxCurrentIndex()
{
    return ui->comboBoxGP8->currentIndex();
}

// Sets the current index of "comboBoxGP0"
void PinFunctionsDialog::setGP0ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP0->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP1"
void PinFunctionsDialog::setGP1ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP1->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP2"
void PinFunctionsDialog::setGP2ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP2->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP3"
void PinFunctionsDialog::setGP3ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP3->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP4"
void PinFunctionsDialog::setGP4ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP4->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP5"
void PinFunctionsDialog::setGP5ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP5->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP6"
void PinFunctionsDialog::setGP6ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP6->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP7"
void PinFunctionsDialog::setGP7ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP7->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP8"
void PinFunctionsDialog::setGP8ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP8->setCurrentIndex(index);
}
