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


// Includes
#include "informationdialog.h"
#include "ui_informationdialog.h"

InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

// Sets the text of "labelManufacturerValue"
void InformationDialog::setManufacturerValueLabelText(const QString &manufacturerString)
{
    QString manufacturer = manufacturerString;
    if (manufacturerString.size() > 26) {
        manufacturer.truncate(24);
        manufacturer += "...";
    }
    ui->labelManufacturerValue->setText(manufacturer);
}

// Sets the text of "labelMaxPowerValue"
void InformationDialog::setMaxPowerValueLabelText(quint8 maxPower)
{
    ui->labelMaxPowerValue->setText(QString("%1 mA [0x%2]").arg(2 * maxPower).arg(maxPower, 2, 16, QChar('0')));
}

// Sets the text of "labelPIDValue"
void InformationDialog::setPIDValueLabelText(quint16 pid)
{
    ui->labelPIDValue->setText(QString("0x%1").arg(pid, 4, 16, QChar('0')));
}

// Sets the text of "labelPowerModeValue"
void InformationDialog::setPowerModeValueLabelText(bool powerMode)
{
    ui->labelPowerModeValue->setText(powerMode ? tr("Self-powered") : tr("Bus-powered"));
}

// Sets the text of "labelProductValue"
void InformationDialog::setProductValueLabelText(const QString &productString)
{
    QString product = productString;
    if (productString.size() > 26) {
        product.truncate(24);
        product += "...";
    }
    ui->labelProductValue->setText(product);
}

// Sets the text of "labelRemoteWakeUpCapableValue"
void InformationDialog::setRemoteWakeUpCapableValueLabelText(bool remoteWakeUpCapable)
{
    ui->labelRemoteWakeUpCapableValue->setText(remoteWakeUpCapable ? tr("Yes") : tr("No"));
}

// Sets the text of "labelSerialValue"
void InformationDialog::setSerialValueLabelText(const QString &serialString)
{
    QString serial = serialString;
    if (serialString.size() > 26) {
        serial.truncate(24);
        serial += "...";
    }
    ui->labelSerialValue->setText(serial);
}

// Sets the text of "labelVIDValue"
void InformationDialog::setVIDValueLabelText(quint16 vid)
{
    ui->labelVIDValue->setText(QString("0x%1").arg(vid, 4, 16, QChar('0')));
}
