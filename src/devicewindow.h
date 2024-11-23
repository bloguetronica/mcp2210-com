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


#ifndef DEVICEWINDOW_H
#define DEVICEWINDOW_H

// Includes
#include <QMainWindow>
#include <QPointer>
#include <QResizeEvent>
#include <QString>
#include <QTimer>
#include "informationdialog.h"
#include "mcp2210.h"
#include "statusdialog.h"

namespace Ui {
class DeviceWindow;
}

class DeviceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceWindow(QWidget *parent = nullptr);
    ~DeviceWindow();

    bool isViewEnabled();
    void openDevice(quint16 vid, quint16 pid, const QString &serialString);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionAbout_triggered();
    void on_actionInformation_triggered();
    void on_actionChangePinFunctions_triggered();
    void on_actionStatus_triggered();
    void update();

private:
    Ui::DeviceWindow *ui;
    MCP2210 mcp2210_;
    MCP2210::ChipSettings chipSettings_;
    QPointer<InformationDialog> informationDialog_;
    QPointer<StatusDialog> statusDialog_;
    QString serialString_;
    QTimer *timer_;
    quint16 pid_, vid_;
    bool viewEnabled_ = false;
    int erracc_ = 0;

    void disableView();
    void initializeGPIOControls();
    void initializeView();
    void readSettings();
    bool validateOperation(const QString &operation, int errcnt, QString errstr);
};

#endif  // DEVICEWINDOW_H
