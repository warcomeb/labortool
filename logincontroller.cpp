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

#include "logincontroller.h"

#include <QDebug>

LoginController::LoginController(QSqlDatabase* db)
{
    m_database = db;

    m_loginDialog = new LoginDialog;

    m_databaseWrapper = new EmployeeDatabase (m_database);

    connect(m_loginDialog, SIGNAL(dataReady(QString,QString)), this, SLOT(checkData(QString,QString)));
}

void LoginController::openDialog()
{
    qDebug() << "LoginController::openDialog()";

    m_loginDialog->exec();

    qDebug() << "LoginController::openDialog() - Exit!";
}

void LoginController::checkData(QString username, QString password)
{
    qDebug() << "LoginController::checkData()";

    qDebug() << "LoginController::checkData() - Username" << username;
    qDebug() << "LoginController::checkData() - Password" << password;

    Employee * employee = new Employee;

    /* TODO: Controllo se il login riesce! */
    if (m_databaseWrapper->getEmployeeByLogin(username,password,employee))
    {
        qDebug() << "LoginController::checkData() - Emit loggedUser()";
        emit loggedUser(employee);
        m_loginDialog->resetField();
        m_loginDialog->close();
    }
    else
    {
        qDebug() << "LoginController::checkData() - Username or password not correct!";
        m_loginDialog->printMessage("Username or password not correct!");
    }

    qDebug() << "LoginController::checkData() - Exit!";
}
