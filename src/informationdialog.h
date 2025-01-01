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


#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

// Includes
#include <QDialog>

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(QWidget *parent = nullptr);
    ~InformationDialog();

    void setManufacturerValueLabelText(const QString &manufacturerString);
    void setMaxPowerValueLabelText(quint8 maxPower);
    void setPIDValueLabelText(quint16 pid);
    void setPowerModeValueLabelText(bool powerMode);
    void setProductValueLabelText(const QString &productString);
    void setRemoteWakeUpCapableValueLabelText(bool remoteWakeUpCapable);
    void setSerialValueLabelText(const QString &serialString);
    void setVIDValueLabelText(quint16 vid);

private:
    Ui::InformationDialog *ui;
};

#endif  // INFORMATIONDIALOG_H
