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
#include "delaysdialog.h"
#include "ui_delaysdialog.h"

DelaysDialog::DelaysDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelaysDialog)
{
    ui->setupUi(this);
}

DelaysDialog::~DelaysDialog()
{
    delete ui;
}

// Returns the value of "spinBoxCSToDataDelay"
quint16 DelaysDialog::csToDataDelaySpinBoxValue()
{
    return static_cast<quint16>(ui->spinBoxCSToDataDelay->value());
}

// Returns the value of "spinBoxDataToCSDelay"
quint16 DelaysDialog::dataToCSDelaySpinBoxValue()
{
    return static_cast<quint16>(ui->spinBoxDataToCSDelay->value());
}

// Returns the value of "spinBoxInterByteDelay"
quint16 DelaysDialog::interByteDelaySpinBoxValue()
{
    return static_cast<quint16>(ui->spinBoxInterByteDelay->value());
}

// Sets the value of "spinBoxCSToDataDelay"
void DelaysDialog::setCSToDataDelaySpinBoxValue(quint16 csToDataDelay)
{
    ui->spinBoxCSToDataDelay->setValue(csToDataDelay);
}

// Sets the value of "spinBoxDataToCSDelay"
void DelaysDialog::setDataToCSDelaySpinBoxValue(quint16 dataToCSDelay)
{
    ui->spinBoxDataToCSDelay->setValue(dataToCSDelay);
}

// Sets the value of "spinBoxInterByteDelay"
void DelaysDialog::setInterByteDelaySpinBoxValue(quint16 interByteDelay)
{
    ui->spinBoxInterByteDelay->setValue(interByteDelay);
}
