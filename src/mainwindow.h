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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includes
#include <QCloseEvent>
#include <QMainWindow>
#include <QMap>
#include <QPointer>
#include <QResizeEvent>
#include <QString>
#include "devicewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionAbout_triggered();
    void on_comboBoxDevices_currentIndexChanged(int index);
    void on_lineEditPID_textEdited(const QString &text);
    void on_lineEditVID_textEdited(const QString &text);
    void on_pushButtonOpen_clicked();
    void on_pushButtonRefresh_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString, QPointer<DeviceWindow>> deviceWindowMap_;
    quint16 pid_, vid_;

    void refresh();
    void validateInput();
};

#endif  // MAINWINDOW_H
