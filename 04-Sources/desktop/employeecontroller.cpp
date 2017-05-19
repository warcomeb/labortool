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

#include "employeecontroller.h"

#include <QDebug>
#include <QMessageBox>

EmployeeController::EmployeeController(QSqlDatabase* db):
    m_loggedUser(0)
{
    m_database = db;

    m_employeeDialog = new EmployeeDialog;

    m_databaseWrapper = new EmployeeDatabase (m_database);
}

EmployeeController::~EmployeeController()
{
    if (m_employeeDialog != 0)
        delete m_employeeDialog;
}

void EmployeeController::translateUi()
{
    m_employeeDialog->translateUi();
}

void EmployeeController::openAddEmployeeDialog ()
{
    qDebug() << "EmployeeController::openAddEmployeeDialog()";

    m_employeeDialog->setOpenType(EmployeeDialog::Add);
    m_employeeDialog->exec();

    Employee * employee = m_employeeDialog->getSavedEmployee();
    if (employee)
    {
        if (m_databaseWrapper->addEmployee(employee))
        {
            qDebug() << "EmployeeController::openAddEmployeeDialog() - Add employee successful";
            QStringList searchParams;
            searchParams << "Active=Yes";
            emit updatedEmployeesList(searchParams);
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "EmployeeController::openAddEmployeeDialog() - Add employee error!";
            QMessageBox::warning(0, tr("Add Employee Error"),
                                 tr("The employee has not been added! Database Error!"));
        }
    }

    delete employee;
}

void EmployeeController::openViewEmployeeDialog (int employeeId)
{
    qDebug() << "EmployeeController::openViewEmployeeDialog()";

    if (employeeId <= 0)
    {
        QMessageBox::warning(0, tr("View Employee Error"),
                             tr("You must select an employee!"));
        return;
    }

    Employee * employee = new Employee;
    if (!m_databaseWrapper->getEmployee(employeeId,employee))
    {
        QMessageBox::warning(0, tr("View Employee Error"),
                             tr("The employee can not be displayed! Database Error!"));

        delete employee;
        return;
    }

    m_employeeDialog->setOpenType(EmployeeDialog::View);
    m_employeeDialog->setSelectedEmployee(employee);

    m_employeeDialog->exec();

    delete employee;
}

void EmployeeController::openEditEmployeeDialog (int employeeId)
{
    qDebug() << "EmployeeController::openEditEmployeeDialog()";

    if (employeeId <= 0)
    {
        QMessageBox::warning(0, tr("Edit Employee Error"),
                             tr("You must select an employee!"));
        return;
    }

    Employee * employee = new Employee;
    if (!m_databaseWrapper->getEmployee(employeeId,employee))
    {
        QMessageBox::warning(0, tr("Edit Employee Error"),
                             tr("The employee can not be edited!\n Database Error!"));

        delete employee;
        return;
    }

    m_employeeDialog->setOpenType(EmployeeDialog::Edit);
    m_employeeDialog->setSelectedEmployee(employee);

    m_employeeDialog->exec();

    employee = m_employeeDialog->getSavedEmployee();
    if (employee)
    {
        if (m_databaseWrapper->updateEmployee(employee))
        {
            qDebug() << "EmployeeController::openEditEmployeeDialog() - Update employee successful";
            QStringList searchParams;
            searchParams << "Active=Yes";
            emit updatedEmployeesList(searchParams);
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "EmployeeController::openEditEmployeeDialog() - Update employee error!";
            QMessageBox::warning(0, tr("Update Employee Error"),
                                 tr("The employee has not been updated! Database Error!"));
        }
    }
    delete employee;
}

QVector<Employee*>
EmployeeController::getEmployeesList (EmployeeController::EmployeesListType type)
{
    qDebug() << "EmployeeController::getEmployeesList(EmployeesListType)";

    switch (type)
    {
    case EmployeeController::Active:
        QStringList searchParams;
        searchParams << "Active=Yes";
        return m_databaseWrapper->searchEmployees(searchParams);
        break;
    }
}


QVector<Employee*>
EmployeeController::getEmployeesList (QStringList searchParams)
{
    qDebug() << "EmployeeController::getEmployeesList(QStringList)";

    return m_databaseWrapper->searchEmployees(searchParams);
}

void EmployeeController::updateLoggedUser(Employee* const employee)
{
    qDebug() << "EmployeeController::updateLoggedUser()";

    m_loggedUser = employee;

    if (m_loggedUser != 0)
    {
        qDebug() << "EmployeeController::updateLoggedUser() - User" << m_loggedUser->getName() << m_loggedUser->getSurname();
        m_employeeDialog->setLoggedUserRole(m_loggedUser->getSystemRole(),
                                            m_loggedUser->getRole());
    }
    else
    {
        /* Low level permission! */
        m_employeeDialog->setLoggedUserRole();
    }
    qDebug() << "EmployeeController::updateLoggedUser() - Exit!";
}
