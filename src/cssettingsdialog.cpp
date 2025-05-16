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


// Includes
#include "cssettingsdialog.h"
#include "ui_cssettingsdialog.h"

CSSettingsDialog::CSSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSSettingsDialog)
{
    ui->setupUi(this);
}

CSSettingsDialog::~CSSettingsDialog()
{
    delete ui;
}

// Returns the state of "checkBoxActiveCS0"
bool CSSettingsDialog::activeCS0CheckBoxIsChecked()
{
    return ui->checkBoxActiveCS0->isChecked();
}

// Returns the state of "checkBoxActiveCS1"
bool CSSettingsDialog::activeCS1CheckBoxIsChecked()
{
    return ui->checkBoxActiveCS1->isChecked();
}

// Returns the state of "checkBoxActiveCS2"
bool CSSettingsDialog::activeCS2CheckBoxIsChecked()
{
    return ui->checkBoxActiveCS2->isChecked();
}

// Returns the state of "checkBoxActiveCS3"
bool CSSettingsDialog::activeCS3CheckBoxIsChecked()
{
    return ui->checkBoxActiveCS3->isChecked();
}

// Returns the state of "checkBoxActiveCS4"
bool CSSettingsDialog::activeCS4CheckBoxIsChecked()
{
    return ui->checkBoxActiveCS4->isChecked();
}

// Returns the state of "checkBoxActiveCS5"
bool CSSettingsDialog::activeCS5CheckBoxIsChecked()
{
    return ui->checkBoxActiveCS5->isChecked();
}

// Returns the state of "checkBoxActiveCS6"
bool CSSettingsDialog::activeCS6CheckBoxIsChecked()
{
    return ui->checkBoxActiveCS6->isChecked();
}

// Returns the state of "checkBoxActiveCS7"
bool CSSettingsDialog::activeCS7CheckBoxIsChecked()
{
    return ui->checkBoxActiveCS7->isChecked();
}

// Returns the state of "checkBoxIdleCS0"
bool CSSettingsDialog::idleCS0CheckBoxIsChecked()
{
    return ui->checkBoxIdleCS0->isChecked();
}

// Returns the state of "checkBoxIdleCS1"
bool CSSettingsDialog::idleCS1CheckBoxIsChecked()
{
    return ui->checkBoxIdleCS1->isChecked();
}

// Returns the state of "checkBoxIdleCS2"
bool CSSettingsDialog::idleCS2CheckBoxIsChecked()
{
    return ui->checkBoxIdleCS2->isChecked();
}

// Returns the state of "checkBoxIdleCS3"
bool CSSettingsDialog::idleCS3CheckBoxIsChecked()
{
    return ui->checkBoxIdleCS3->isChecked();
}

// Returns the state of "checkBoxIdleCS4"
bool CSSettingsDialog::idleCS4CheckBoxIsChecked()
{
    return ui->checkBoxIdleCS4->isChecked();
}

// Returns the state of "checkBoxIdleCS5"
bool CSSettingsDialog::idleCS5CheckBoxIsChecked()
{
    return ui->checkBoxIdleCS5->isChecked();
}

// Returns the state of "checkBoxIdleCS6"
bool CSSettingsDialog::idleCS6CheckBoxIsChecked()
{
    return ui->checkBoxIdleCS6->isChecked();
}

// Returns the state of "checkBoxIdleCS7"
bool CSSettingsDialog::idleCS7CheckBoxIsChecked()
{
    return ui->checkBoxIdleCS7->isChecked();
}

// Sets the state of "checkBoxActiveCS0"
void CSSettingsDialog::setActiveCS0CheckBox(bool cs0ActiveLevel)
{
    ui->checkBoxActiveCS0->setChecked(cs0ActiveLevel);
}

// Sets the state of "checkBoxActiveCS1"
void CSSettingsDialog::setActiveCS1CheckBox(bool cs1ActiveLevel)
{
    ui->checkBoxActiveCS1->setChecked(cs1ActiveLevel);
}

// Sets the state of "checkBoxActiveCS2"
void CSSettingsDialog::setActiveCS2CheckBox(bool cs2ActiveLevel)
{
    ui->checkBoxActiveCS2->setChecked(cs2ActiveLevel);
}

// Sets the state of "checkBoxActiveCS3"
void CSSettingsDialog::setActiveCS3CheckBox(bool cs3ActiveLevel)
{
    ui->checkBoxActiveCS3->setChecked(cs3ActiveLevel);
}

// Sets the state of "checkBoxActiveCS4"
void CSSettingsDialog::setActiveCS4CheckBox(bool cs4ActiveLevel)
{
    ui->checkBoxActiveCS4->setChecked(cs4ActiveLevel);
}

// Sets the state of "checkBoxActiveCS5"
void CSSettingsDialog::setActiveCS5CheckBox(bool cs5ActiveLevel)
{
    ui->checkBoxActiveCS5->setChecked(cs5ActiveLevel);
}

// Sets the state of "checkBoxActiveCS6"
void CSSettingsDialog::setActiveCS6CheckBox(bool cs6ActiveLevel)
{
    ui->checkBoxActiveCS6->setChecked(cs6ActiveLevel);
}

// Sets the state of "checkBoxActiveCS7"
void CSSettingsDialog::setActiveCS7CheckBox(bool cs7ActiveLevel)
{
    ui->checkBoxActiveCS7->setChecked(cs7ActiveLevel);
}

// Sets the state of "checkBoxIdleCS0"
void CSSettingsDialog::setIdleCS0CheckBox(bool cs0IdleLevel)
{
    ui->checkBoxIdleCS0->setChecked(cs0IdleLevel);
}

// Sets the state of "checkBoxIdleCS1"
void CSSettingsDialog::setIdleCS1CheckBox(bool cs1IdleLevel)
{
    ui->checkBoxIdleCS1->setChecked(cs1IdleLevel);
}

// Sets the state of "checkBoxIdleCS2"
void CSSettingsDialog::setIdleCS2CheckBox(bool cs2IdleLevel)
{
    ui->checkBoxIdleCS2->setChecked(cs2IdleLevel);
}

// Sets the state of "checkBoxIdleCS3"
void CSSettingsDialog::setIdleCS3CheckBox(bool cs3IdleLevel)
{
    ui->checkBoxIdleCS3->setChecked(cs3IdleLevel);
}

// Sets the state of "checkBoxIdleCS4"
void CSSettingsDialog::setIdleCS4CheckBox(bool cs4IdleLevel)
{
    ui->checkBoxIdleCS4->setChecked(cs4IdleLevel);
}

// Sets the state of "checkBoxIdleCS5"
void CSSettingsDialog::setIdleCS5CheckBox(bool cs5IdleLevel)
{
    ui->checkBoxIdleCS5->setChecked(cs5IdleLevel);
}

// Sets the state of "checkBoxIdleCS6"
void CSSettingsDialog::setIdleCS6CheckBox(bool cs6IdleLevel)
{
    ui->checkBoxIdleCS6->setChecked(cs6IdleLevel);
}

// Sets the state of "checkBoxIdleCS7"
void CSSettingsDialog::setIdleCS7CheckBox(bool cs7IdleLevel)
{
    ui->checkBoxIdleCS7->setChecked(cs7IdleLevel);
}
