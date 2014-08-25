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

#include "employee.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QMetaEnum>

Employee::Employee(const QString &surname, const QString &name)
{
    m_surname = surname;
    m_name = name;
}

Employee::Employee()
{
}

void Employee::setId (uint id)
{
    m_id = id;
}

void Employee::setName (QString name)
{
    m_name = name;
}

void Employee::setSurname (QString surname)
{
    m_surname = surname;
}

void Employee::setUsername (QString username)
{
    m_username = username;
}

/**
 * @brief Employee::setPassword
 * @param password Password of the user
 *
 * Questo metodo salva la password dell'utente e ne
 * effettua la criptazione.
 */
void Employee::setPassword (QString password)
{
    QByteArray hash;

    qDebug() << "The password is:" << password;
    hash.append(password);
    hash = QCryptographicHash::hash(hash,QCryptographicHash::Sha1);
    qDebug() << "The hashed byte array is:" << hash;
    m_password = QString(hash.toHex());
    qDebug() << "The hashed password is:" << m_password.toUtf8();
}

void Employee::setRole (Employee::Role role)
{
    m_role = role;
}

void Employee::setSystemRole (Employee::SystemRole systemRole)
{
    m_systemRole = systemRole;
}

void Employee::setCompany (Employee::Company company)
{
    m_company = company;
}

void Employee::setActiveStatus (Employee::Active active)
{
    m_active = active;
}

void Employee::setRole (QString role)
{
    qDebug() << "Employee::setRole()";
    QByteArray bytearray = role.toLocal8Bit();
    qDebug() << "Employee::setRole() - string value" << role;

    int value = Employee::staticMetaObject.enumerator(
                 Employee::staticMetaObject.indexOfEnumerator("Role")).
                 keysToValue(bytearray.data());

    qDebug() << "Employee::setRole() - value" << value;
    m_role = static_cast<Employee::Role>(value);
}

void Employee::setSystemRole (QString systemRole)
{
    qDebug() << "Employee::setSystemRole()";
    QByteArray bytearray = systemRole.toLocal8Bit();
    qDebug() << "Employee::setSystemRole() - string value" << systemRole;

    int value = Employee::staticMetaObject.enumerator(
                 Employee::staticMetaObject.indexOfEnumerator("SystemRole")).
                 keysToValue(bytearray.data());

    qDebug() << "Employee::setSystemRole() - value" << value;
    m_systemRole = static_cast<Employee::SystemRole>(value);
}

void Employee::setCompany (QString company)
{
    qDebug() << "Employee::setCompany()";
    QByteArray bytearray = company.toLocal8Bit();
    qDebug() << "Employee::setCompany() - string value" << company;

    int value = Employee::staticMetaObject.enumerator(
                 Employee::staticMetaObject.indexOfEnumerator("Company")).
                 keysToValue(bytearray.data());

    qDebug() << "Employee::setCompany() - value" << value;
    m_company = static_cast<Employee::Company>(value);
}

void Employee::setActiveStatus(QString active)
{
    qDebug() << "Employee::setActiveStatus()";
    QByteArray bytearray = active.toLocal8Bit();
    qDebug() << "Employee::setActiveStatus() - string value" << active;

    int value = Employee::staticMetaObject.enumerator(
                 Employee::staticMetaObject.indexOfEnumerator("Active")).
                 keysToValue(bytearray.data());

    qDebug() << "Employee::setActiveStatus() - value" << value;
    m_active = static_cast<Employee::Active>(value);
}

void Employee::setNote (QString note)
{
    m_note = note;
}

QString Employee::getRoleString (Employee::Role value)
{
    return Employee::staticMetaObject.enumerator(
                Employee::staticMetaObject.indexOfEnumerator("Role")).
                valueToKey(value);
}

QString Employee::getSystemRoleString (Employee::SystemRole value)
{
    return Employee::staticMetaObject.enumerator(
                Employee::staticMetaObject.indexOfEnumerator("SystemRole")).
                valueToKey(value);
}

QString Employee::getCompanyString (Employee::Company value)
{
    return Employee::staticMetaObject.enumerator(
                Employee::staticMetaObject.indexOfEnumerator("Company")).
                valueToKey(value);
}

QString Employee::getActiveStatusString (Employee::Active value)
{
    return Employee::staticMetaObject.enumerator(
                Employee::staticMetaObject.indexOfEnumerator("Active")).
                valueToKey(value);
}
