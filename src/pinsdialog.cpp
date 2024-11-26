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
#include "pinsdialog.h"
#include "ui_pinsdialog.h"

PinsDialog::PinsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinsDialog)
{
    ui->setupUi(this);
}

PinsDialog::~PinsDialog()
{
    delete ui;
}

// Returns the current index of "comboBoxGP0"
int PinsDialog::gp0ComboBoxCurrentIndex()
{
    return ui->comboBoxGP0->currentIndex();
}

// Returns the current index of "comboBoxGP1"
int PinsDialog::gp1ComboBoxCurrentIndex()
{
    return ui->comboBoxGP1->currentIndex();
}

// Returns the current index of "comboBoxGP2"
int PinsDialog::gp2ComboBoxCurrentIndex()
{
    return ui->comboBoxGP2->currentIndex();
}

// Returns the current index of "comboBoxGP3"
int PinsDialog::gp3ComboBoxCurrentIndex()
{
    return ui->comboBoxGP3->currentIndex();
}

// Returns the current index of "comboBoxGP4"
int PinsDialog::gp4ComboBoxCurrentIndex()
{
    return ui->comboBoxGP4->currentIndex();
}

// Returns the current index of "comboBoxGP5"
int PinsDialog::gp5ComboBoxCurrentIndex()
{
    return ui->comboBoxGP5->currentIndex();
}

// Returns the current index of "comboBoxGP6"
int PinsDialog::gp6ComboBoxCurrentIndex()
{
    return ui->comboBoxGP6->currentIndex();
}

// Returns the current index of "comboBoxGP7"
int PinsDialog::gp7ComboBoxCurrentIndex()
{
    return ui->comboBoxGP7->currentIndex();
}

// Returns the current index of "comboBoxGP8"
int PinsDialog::gp8ComboBoxCurrentIndex()
{
    return ui->comboBoxGP8->currentIndex();
}

// Sets the current index of "comboBoxGP0"
void PinsDialog::setGP0ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP0->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP1"
void PinsDialog::setGP1ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP1->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP2"
void PinsDialog::setGP2ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP2->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP3"
void PinsDialog::setGP3ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP3->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP4"
void PinsDialog::setGP4ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP4->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP5"
void PinsDialog::setGP5ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP5->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP6"
void PinsDialog::setGP6ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP6->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP7"
void PinsDialog::setGP7ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP7->setCurrentIndex(index);
}

// Sets the current index of "comboBoxGP8"
void PinsDialog::setGP8ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP8->setCurrentIndex(index);
}
