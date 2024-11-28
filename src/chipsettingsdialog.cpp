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
#include "chipsettingsdialog.h"
#include "ui_chipsettingsdialog.h"

ChipSettingsDialog::ChipSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChipSettingsDialog)
{
    ui->setupUi(this);
}

ChipSettingsDialog::~ChipSettingsDialog()
{
    delete ui;
}

// Returns the current index of "comboBoxGP0"
int ChipSettingsDialog::gp0ComboBoxCurrentIndex()
{
    return ui->comboBoxGP0->currentIndex();
}

// Returns the state of "checkBoxGP0DefaultValue"
bool ChipSettingsDialog::gp0DefaultValueCheckBoxIsChecked()
{
    return ui->checkBoxGP0DefaultValue->isChecked();
}

// Returns the current index of "comboBoxGP1"
int ChipSettingsDialog::gp1ComboBoxCurrentIndex()
{
    return ui->comboBoxGP1->currentIndex();
}

// Returns the state of "checkBoxGP1DefaultValue"
bool ChipSettingsDialog::gp1DefaultValueCheckBoxIsChecked()
{
    return ui->checkBoxGP1DefaultValue->isChecked();
}

// Returns the current index of "comboBoxGP2"
int ChipSettingsDialog::gp2ComboBoxCurrentIndex()
{
    return ui->comboBoxGP2->currentIndex();
}

// Returns the state of "checkBoxGP2DefaultValue"
bool ChipSettingsDialog::gp2DefaultValueCheckBoxIsChecked()
{
    return ui->checkBoxGP2DefaultValue->isChecked();
}

// Returns the current index of "comboBoxGP3"
int ChipSettingsDialog::gp3ComboBoxCurrentIndex()
{
    return ui->comboBoxGP3->currentIndex();
}

// Returns the state of "checkBoxGP3DefaultValue"
bool ChipSettingsDialog::gp3DefaultValueCheckBoxIsChecked()
{
    return ui->checkBoxGP3DefaultValue->isChecked();
}

// Returns the current index of "comboBoxGP4"
int ChipSettingsDialog::gp4ComboBoxCurrentIndex()
{
    return ui->comboBoxGP4->currentIndex();
}

// Returns the state of "checkBoxGP4DefaultValue"
bool ChipSettingsDialog::gp4DefaultValueCheckBoxIsChecked()
{
    return ui->checkBoxGP4DefaultValue->isChecked();
}

// Returns the current index of "comboBoxGP5"
int ChipSettingsDialog::gp5ComboBoxCurrentIndex()
{
    return ui->comboBoxGP5->currentIndex();
}

// Returns the state of "checkBoxGP5DefaultValue"
bool ChipSettingsDialog::gp5DefaultValueCheckBoxIsChecked()
{
    return ui->checkBoxGP5DefaultValue->isChecked();
}

// Returns the current index of "comboBoxGP6"
int ChipSettingsDialog::gp6ComboBoxCurrentIndex()
{
    return ui->comboBoxGP6->currentIndex();
}

// Returns the state of "checkBoxGP6DefaultValue"
bool ChipSettingsDialog::gp6DefaultValueCheckBoxIsChecked()
{
    return ui->checkBoxGP6DefaultValue->isChecked();
}

// Returns the current index of "comboBoxGP7"
int ChipSettingsDialog::gp7ComboBoxCurrentIndex()
{
    return ui->comboBoxGP7->currentIndex();
}

// Returns the state of "checkBoxGP7DefaultValue"
bool ChipSettingsDialog::gp7DefaultValueCheckBoxIsChecked()
{
    return ui->checkBoxGP7DefaultValue->isChecked();
}

// Returns the current index of "comboBoxGP8"
int ChipSettingsDialog::gp8ComboBoxCurrentIndex()
{
    return ui->comboBoxGP8->currentIndex();
}

// Sets the current index of "comboBoxGP0"
void ChipSettingsDialog::setGP0ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP0->setCurrentIndex(index);
}

// Sets the state of "comboBoxGP0"
void ChipSettingsDialog::setGP0DefaultValueCheckBox(bool state)
{
   ui->checkBoxGP0DefaultValue->setChecked(state);
}

// Sets the current index of "comboBoxGP1"
void ChipSettingsDialog::setGP1ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP1->setCurrentIndex(index);
}

// Sets the state of "comboBoxGP1"
void ChipSettingsDialog::setGP1DefaultValueCheckBox(bool state)
{
    ui->checkBoxGP1DefaultValue->setChecked(state);
}

// Sets the current index of "comboBoxGP2"
void ChipSettingsDialog::setGP2ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP2->setCurrentIndex(index);
}

// Sets the state of "comboBoxGP2"
void ChipSettingsDialog::setGP2DefaultValueCheckBox(bool state)
{
    ui->checkBoxGP2DefaultValue->setChecked(state);
}

// Sets the current index of "comboBoxGP3"
void ChipSettingsDialog::setGP3ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP3->setCurrentIndex(index);
}

// Sets the state of "comboBoxGP3"
void ChipSettingsDialog::setGP3DefaultValueCheckBox(bool state)
{
    ui->checkBoxGP3DefaultValue->setChecked(state);
}

// Sets the current index of "comboBoxGP4"
void ChipSettingsDialog::setGP4ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP4->setCurrentIndex(index);
}

// Sets the state of "comboBoxGP4"
void ChipSettingsDialog::setGP4DefaultValueCheckBox(bool state)
{
    ui->checkBoxGP4DefaultValue->setChecked(state);
}

// Sets the current index of "comboBoxGP5"
void ChipSettingsDialog::setGP5ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP5->setCurrentIndex(index);
}

// Sets the state of "comboBoxGP5"
void ChipSettingsDialog::setGP5DefaultValueCheckBox(bool state)
{
    ui->checkBoxGP5DefaultValue->setChecked(state);
}

// Sets the current index of "comboBoxGP6"
void ChipSettingsDialog::setGP6ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP6->setCurrentIndex(index);
}

// Sets the state of "comboBoxGP6"
void ChipSettingsDialog::setGP6DefaultValueCheckBox(bool state)
{
    ui->checkBoxGP6DefaultValue->setChecked(state);
}

// Sets the current index of "comboBoxGP7"
void ChipSettingsDialog::setGP7ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP7->setCurrentIndex(index);
}

// Sets the state of "comboBoxGP7"
void ChipSettingsDialog::setGP7DefaultValueCheckBox(bool state)
{
    ui->checkBoxGP7DefaultValue->setChecked(state);
}

// Sets the current index of "comboBoxGP8"
void ChipSettingsDialog::setGP8ComboBoxCurrentIndex(int index)
{
    ui->comboBoxGP8->setCurrentIndex(index);
}
