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


#ifndef DELAYSDIALOG_H
#define DELAYSDIALOG_H

// Includes
#include <QDialog>

namespace Ui {
class DelaysDialog;
}

class DelaysDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelaysDialog(QWidget *parent = nullptr);
    ~DelaysDialog();

    quint16 csToDataDelaySpinBoxValue();
    quint16 dataToCSDelaySpinBoxValue();
    quint16 interByteDelaySpinBoxValue();
    void setCSToDataDelaySpinBoxValue(quint16 csToDataDelay);
    void setDataToCSDelaySpinBoxValue(quint16 dataToCSDelay);
    void setInterByteDelaySpinBoxValue(quint16 interByteDelay);

private:
    Ui::DelaysDialog *ui;
};

#endif  // DELAYSDIALOG_H
