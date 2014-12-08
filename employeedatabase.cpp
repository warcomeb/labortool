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

bool EmployeeDatabase::getEmployee (int id, Employee* employee)
{
    qDebug() << "EmployeeDatabase::getEmployee()";

    QString queryString = "SELECT * FROM employee WHERE EmployeeId='" +
            QString::number(id) + "'";

    qDebug() << "EmployeeDatabase::getEmployee() - Final search string: " << queryString;
    QSqlQuery query( queryString, *m_database);

    if (query.size() != 1)
    {
        qDebug() << "EmployeeDatabase::getEmployee() - database problems!";
        return false;
    }

    /* Read record! */
    qDebug() << "EmployeeDatabase::getEmployee() - read record";
    query.next();

    employee->setId(id);
    employee->setName(query.value(1).toString());
    employee->setSurname(query.value(2).toString());
    employee->setUsername(query.value(3).toString());
    /* Do not use the password field! */
//    employee->setPassword(query.value(4).toString());
    employee->setNote(query.value(5).toString());
    employee->setRole(query.value(6).toString());
    employee->setSystemRole(query.value(7).toString());
    employee->setCompany(query.value(8).toString());
    employee->setActiveStatus(query.value(9).toString());

    qDebug() << "EmployeeDatabase::getEmployee() - employee" << id <<
                query.value(2).toString() << query.value(1).toString();
    return true;
}

bool EmployeeDatabase::getEmployeeByLogin(QString username,
                                          QString password,
                                          Employee* employee)
{
    qDebug() << "EmployeeDatabase::getEmployeeByLogin()";

    QString queryString = "SELECT * FROM employee WHERE ("
            "EmployeeUsername='" + username + "' AND "
            "EmployeePassword='" + password + "')";

    qDebug() << "EmployeeDatabase::getEmployeeByLogin() - Final search string: " << queryString;
    QSqlQuery query( queryString, *m_database);

    if (query.size() != 1)
    {
        qDebug() << "EmployeeDatabase::getEmployee() - database problems!";
        return false;
    }

    /* Read record! */
    qDebug() << "EmployeeDatabase::getEmployee() - read record";
    query.next();

    employee->setId(query.value(0).toString().toUInt());
    employee->setName(query.value(1).toString());
    employee->setSurname(query.value(2).toString());
    employee->setUsername(query.value(3).toString());
    /* Do not use the password field! */
//    employee->setPassword(query.value(4).toString());
    employee->setNote(query.value(5).toString());
    employee->setRole(query.value(6).toString());
    employee->setSystemRole(query.value(7).toString());
    employee->setCompany(query.value(8).toString());
    employee->setActiveStatus(query.value(9).toString());

    qDebug() << "EmployeeDatabase::getEmployeeByLogin() - Exit!";
    return true;
}

/* TODO: Update completo della riga */

bool EmployeeDatabase::updateEmployee (Employee* employee)
{
    qDebug() << "EmployeeDatabase::updateEmployee()";

    QSqlQuery query(*m_database);
    QString queryString = "UPDATE employee SET "
            "EmployeeName=:name ,"
            "EmployeeSurname=:surname ,"
            "EmployeeUsername=:user ,"
            "EmployeeNote=:note ,"
            "EmployeeRole=:role ,"
            "EmployeeSysRole=:sysrole ,"
            "EmployeeCompany=:company ,"
            "EmployeeActive=:active "
            "WHERE EmployeeId=:rowid";

    query.prepare(queryString);
    query.bindValue(":name",employee->getName());
    query.bindValue(":surname",employee->getSurname());
    query.bindValue(":user",employee->getUsername());
    query.bindValue(":note",employee->getNote());
    query.bindValue(":role",Employee::getRoleString(employee->getRole()));
    query.bindValue(":sysrole",Employee::getSystemRoleString(employee->getSystemRole()));
    query.bindValue(":company",Employee::getCompanyString(employee->getCompany()));
    query.bindValue(":active",Employee::getActiveStatusString(employee->getActiveStatus()));
    query.bindValue(":rowid",QString::number(employee->getId()));

    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 0 " << query.boundValue(0);
    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 1 " << query.boundValue(1);
    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 2 " << query.boundValue(2);
    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 3 " << query.boundValue(3);
    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 4 " << query.boundValue(4);
    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 5 " << query.boundValue(5);
    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 6 " << query.boundValue(6);
    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 7 " << query.boundValue(7);
    qDebug() << "EmployeeDatabase::updateEmployee() - Bound Value 8 " << query.boundValue(8);

    if (query.exec())
    {
        qDebug() << "EmployeeDatabase::updateEmployee() - " << query.lastQuery();
        qDebug() << "EmployeeDatabase::updateEmployee() - " << query.lastError();
        qDebug() << "EmployeeDatabase::updateEmployee() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "EmployeeDatabase::updateEmployee() - " << query.lastQuery();
        qDebug() << "EmployeeDatabase::updateEmployee() - " << query.lastError();
        return false;
    }
}

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

            if (searchParams.at(i).indexOf('=') != -1)
            {
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
                    return employeesList;
                }

            }
            else if (searchParams.at(i).indexOf('%') != -1)
            {
                QStringList searchParam = searchParams.at(i).split('%');
                if (searchParam.size() == 2)
                {
                    qDebug() << "EmployeeDatabase::searchEmployees() - Param is correct";
                    queryString.append(
                        "( EmployeeName LIKE '%" + searchParam.at(1) + "%' OR " +
                        "EmployeeSurname LIKE '%" + searchParam.at(1) + "%' OR " +
                        "EmployeeUsername LIKE '%" + searchParam.at(1) + "%' OR " +
                        "EmployeeNote LIKE '%" + searchParam.at(1) + "%') "
                    );
                }
                else
                {
                    qDebug() << "EmployeeDatabase::searchEmployees() - Param is not correct";
                    return employeesList;
                }

            }
            else if (searchParams.at(i).indexOf('$') != -1)
            {
                QStringList searchParam = searchParams.at(i).split('$');
                if (searchParam.size() == 2)
                {
                    qDebug() << "EmployeeDatabase::searchEmployees() - Param is correct";
                    qDebug() << "EmployeeDatabase::searchEmployees()" << searchParam;
                    QStringList searchComboParams = searchParam.at(1).split('|');
                    queryString.append("( ");
                    for (int j = 0; j < searchComboParams.size(); ++j)
                    {
                        queryString.append(DB_FIELD_SUFFIX +
                                           searchParam.at(0) +  "='" +
                                           searchComboParams.at(i) + "' ");

                        if (j+1 == searchComboParams.size())
                            queryString.append(") ");
                        else
                            queryString.append("OR ");
                    }
                }
                else
                {
                    qDebug() << "EmployeeDatabase::searchEmployees() - Param is not correct";
                    return employeesList;
                }
            }
            else
            {
                qDebug() << "EmployeeDatabase::searchEmployees() - Param is not correct";
                return employeesList;
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
    qDebug() << "EmployeeDatabase::searchEmployees() - Query executed!";
    while (query.next())
    {
        qDebug() << "EmployeeDatabase::searchEmployees() - Query result...";
        QVector<QString> employee;
        employee.append(query.value(0).toString()); // Id
        employee.append(query.value(1).toString()); // Surname
        employee.append(query.value(2).toString()); // Name
        employee.append(query.value(3).toString()); // Username
        employee.append(query.value(4).toString()); // Role

        qDebug() << "EmployeeDatabase::searchEmployees() - query to vector ok!";

        employeesList.append(employee);
        qDebug() << "EmployeeDatabase::searchEmployees() - vector added!";
    }

    qDebug() << "EmployeeDatabase::searchEmployees() - Final list" << employeesList;
    return employeesList;
}
