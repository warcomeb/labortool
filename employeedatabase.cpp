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

#include "employeedatabase.h"

#include <QVariant>
#include <QSqlError>

#define DB_FIELD_SUFFIX     "Employee"

EmployeeDatabase::EmployeeDatabase(QSqlDatabase *db)
{
    m_database = db;
}

bool EmployeeDatabase::addEmployee (Employee* employee)
{
    qDebug() << "EmployeeDatabase::addEmployee()";

    QSqlQuery query(*m_database);
    QString queryString = "INSERT INTO employee "
                          "(EmployeeSurname, EmployeeName, EmployeeUsername, EmployeePassword, "
                          "EmployeeRole, EmployeeSysRole, EmployeeCompany, EmployeeActive, EmployeeNote)"
                          " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

    query.prepare(queryString);
    query.bindValue(0,employee->getSurname());
    query.bindValue(1,employee->getName());
    query.bindValue(2,employee->getUsername());
    query.bindValue(3,employee->getPassword());
    query.bindValue(4,Employee::getRoleString(employee->getRole()));
    query.bindValue(5,Employee::getSystemRoleString(employee->getSystemRole()));
    query.bindValue(6,Employee::getCompanyString(employee->getCompany()));
    query.bindValue(7,Employee::getActiveStatusString(employee->getActiveStatus()));
    query.bindValue(8,employee->getNote());

    qDebug() << "EmployeeDatabase::addEmployee() - " << query.lastQuery();

    if (query.exec())
    {
        qDebug() << "EmployeeDatabase::addEmployee() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "EmployeeDatabase::addEmployee() - "<< query.lastError();
        return false;
    }
}

bool EmployeeDatabase::getEmployee (uint id, Employee* employee)
{
    return true;
}

bool EmployeeDatabase::updateEmployee (Employee* employee)
{
return true;
}

//QVector< QVector<QString> > EmployeeDatabase::getActiveEmployees()
//{
//    qDebug() << "EmployeeDatabase::getActiveEmployees()";

//    QVector<QVector<QString> > employeesList;
//    QString queryString = "SELECT EmployeeId, EmployeeSurname, EmployeeName, "
//                          "EmployeeUsername, EmployeeRole FROM employee "
//                          "WHERE EmployeeActive='Yes' "
//                          "ORDER BY EmployeeSurname ASC";

//    QSqlQuery query( queryString, *m_database);
//    while (query.next())
//    {
//        QVector<QString> employee;
//        employee.append(query.value(0).toString()); // Id
//        employee.append(query.value(1).toString()); // Surname
//        employee.append(query.value(2).toString()); // Name
//        employee.append(query.value(3).toString()); // Username
//        employee.append(query.value(4).toString()); // Role

//        employeesList.append(employee);
//    }

//    return employeesList;
//}

/* TODO: Encoding dei caratteri particolari. */
QVector< QVector< QString > >
EmployeeDatabase::searchEmployees(QStringList searchParams)
{
    qDebug() << "EmployeeDatabase::searchEmployees()";

    QVector<QVector<QString> > employeesList;
    QString queryString = "SELECT EmployeeId, EmployeeSurname, EmployeeName, "
                          "EmployeeUsername, EmployeeRole FROM employee ";

    if (searchParams.size()>0)
    {
        qDebug() << "EmployeeDatabase::searchEmployees() - Search param list is not empty";

        queryString.append("WHERE ( ");
        for (int i = 0; i < searchParams.size(); ++i)
        {
            qDebug() << "EmployeeDatabase::searchEmployees() - Param:" << searchParams.at(i);

            QStringList searchParam = searchParams.at(i).split('=');
            if (searchParam.size() == 2)
            {
                qDebug() << "EmployeeDatabase::searchEmployees() - Param is correct";
                queryString.append(DB_FIELD_SUFFIX +
                                   searchParam.at(0) +  "='" +
                                   searchParam.at(1) + "' ");
            }
            else
            {
                qDebug() << "EmployeeDatabase::searchEmployees() - Param is not correct";
            }

            if (i+1 == searchParams.size())
                queryString.append(") ");
            else
                queryString.append(" AND ");
        }
    }
    queryString.append("ORDER BY EmployeeSurname ASC");

    qDebug() << "EmployeeDatabase::searchEmployees() - Final search string: " << queryString;

    QSqlQuery query( queryString, *m_database);
    while (query.next())
    {
        QVector<QString> employee;
        employee.append(query.value(0).toString()); // Id
        employee.append(query.value(1).toString()); // Surname
        employee.append(query.value(2).toString()); // Name
        employee.append(query.value(3).toString()); // Username
        employee.append(query.value(4).toString()); // Role

        employeesList.append(employee);
    }

    return employeesList;
}
