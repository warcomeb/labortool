/******************************************************************************
 * LabOrTool - Laboratory Organization Tool
 * Copyright (C) 2014 Marco Giammarini
 *
 * Author(s):
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>

#include <QStandardItemModel>

#include "activitycontroller.h"
#include "employeecontroller.h"
#include "logincontroller.h"

#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    bool connectToDatabase ();
    bool disconnectToDatabase ();

    void updateSelectedTab (int index);

    void openActivityDialog ();
    void openEmployeeDialog ();

    void selectionChangedEmployeesTable (const QItemSelection & sel, const QItemSelection & des);
    void updateEmployeesTable (QStringList searchParams);
    void searchEmployees ();
    void resetSearchEmployees ();

    void selectionChangedActivitiesTable (const QItemSelection & sel, const QItemSelection & des);
    void updateActivitiesTable (QStringList searchParams);
    void searchActivities ();
    void resetSearchActivities ();

    void userLogin ();
    void userLogout ();

private:
    Ui::MainWindow *ui;

    QSqlDatabase m_database;

    /* Controllers list */
    ActivityController * m_activityController;
    EmployeeController * m_employeeController;
    LoginController * m_loginController;

    /* Models */
    QStandardItemModel * m_employeeModel;
    int m_employeeSelected;
    QStandardItemModel * m_activityModel;
    int m_activitySelected;

    void initBasicCommand();

    /* Initialize signals and slots into tabs */
    void initActivityTab();
    void initEmployeeTab();

};

#endif // MAINWINDOW_H
