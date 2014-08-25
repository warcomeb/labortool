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

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <QString>

class Employee : public QObject
{
    Q_OBJECT
    Q_ENUMS(Role SystemRole Company Active)
    Q_PROPERTY(Role role READ getRole WRITE setRole)
    Q_PROPERTY(SystemRole systemRole READ getSystemRole WRITE setSystemRole)
    Q_PROPERTY(Company company READ getCompany WRITE setCompany)
    Q_PROPERTY(Active active READ getActiveStatus WRITE setActiveStatus)

public:
    Employee(const QString &surname, const QString &name);
    Employee();

    typedef enum
    {
        Coordinator,
        SeniorDesigner,
        Designer,
        Technician,
        Student,
    } Role;

    typedef enum
    {
        Administrator,
        Editor,
        User,
    } SystemRole;

    typedef enum
    {
        Aea,
        Gi,
        Extern
    } Company;

    typedef enum
    {
        Yes,
        No,
    } Active;

    uint getId () const { return m_id; }

    QString getName () const { return m_name; }
    QString getSurname () const { return m_surname; }

    QString getUsername () const { return m_username; }
    QString getPassword () const { return m_password; }

    Role getRole () const { return m_role; }
    SystemRole getSystemRole () const { return m_systemRole; }
    Company getCompany () const { return m_company; }
    Active getActiveStatus () const { return m_active; }

    QString getNote () const { return m_note; }

    void setId (uint id);
    void setName (QString);
    void setSurname (QString);

    void setUsername (QString username);
    void setPassword (QString password);

    void setRole (Role role);
    void setSystemRole (SystemRole systemRole);
    void setCompany (Company company);
    void setActiveStatus (Active active);

    void setRole(QString role);
    void setSystemRole (QString systemRole);
    void setCompany (QString company);
    void setActiveStatus (QString active);

    void setNote (QString note);

    static QString getCompanyString (Company value);
    static QString getRoleString (Role value);
    static QString getSystemRoleString (SystemRole value);
    static QString getActiveStatusString (Active value);

private:
    uint m_id;
    QString m_name;
    QString m_surname;

    QString m_username;
    QString m_password;

    Role       m_role;
    SystemRole m_systemRole;
    Company    m_company;
    Active     m_active;

    QString    m_note;
};

#endif // EMPLOYEE_H
