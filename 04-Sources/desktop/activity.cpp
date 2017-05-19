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

#include "activity.h"

#include <QDebug>
#include <QMetaEnum>

Activity::Activity(QString title):
    m_assignedEmployee(0)
{
    m_title = title;
}

Activity::Activity():
    m_assignedEmployee(0)
{
}

void Activity::setId (uint id)
{
    m_id = id;
}

void Activity::setTitle (QString title)
{
    m_title = title;
}

void Activity::setDescription (QString description)
{
    m_description =  description;
}

void Activity::setWorkCode (QString code)
{
    m_workCode = code;
}

void Activity::setDeadline (QDate deadline)
{
    m_deadline = deadline;
}

void Activity::setDeadline (QString deadline)
{
    m_deadline = QDate::fromString(deadline,"yyyy-MM-dd");
}

void Activity::setEmployee (uint employee)
{
    m_assignedEmployee = employee;
}

void Activity::setStatus(Activity::Status status)
{
    m_status = status;
}

void Activity::setType(Activity::Type type)
{
    m_type = type;
}

void Activity::setPriority(Activity::Priority priority)
{
    m_priority = priority;
}

void Activity::setStatus(QString status)
{
    qDebug() << "Activity::setStatus()";
    QByteArray bytearray = status.toLocal8Bit();
    qDebug() << "Activity::setStatus() - string value" << status;

    int value = Activity::staticMetaObject.enumerator(
                 Activity::staticMetaObject.indexOfEnumerator("Status")).
                 keysToValue(bytearray.data());

    qDebug() << "Activity::setStatus() - value" << value;
    m_status = static_cast<Activity::Status>(value);
}

void Activity::setType(QString type)
{
    qDebug() << "Activity::setType()";
    QByteArray bytearray = type.toLocal8Bit();
    qDebug() << "Activity::setType() - string value" << type;

    int value = Activity::staticMetaObject.enumerator(
                 Activity::staticMetaObject.indexOfEnumerator("Type")).
                 keysToValue(bytearray.data());

    qDebug() << "Activity::setType() - value" << value;
    m_type = static_cast<Activity::Type>(value);
}

void Activity::setPriority(QString priority)
{
    qDebug() << "Activity::setPriority()";
    QByteArray bytearray = priority.toLocal8Bit();
    qDebug() << "Activity::setPriority() - string value" << priority;

    int value = Activity::staticMetaObject.enumerator(
                 Activity::staticMetaObject.indexOfEnumerator("Priority")).
                 keysToValue(bytearray.data());

    qDebug() << "Activity::setPriority() - value" << value;
    m_priority = static_cast<Activity::Priority>(value);
}

QString Activity::getStatusString (Activity::Status value)
{
    return Activity::staticMetaObject.enumerator(
                Activity::staticMetaObject.indexOfEnumerator("Status")).
                valueToKey(value);
}

QString Activity::getFormattedStatusString (Activity::Status value)
{
    switch (value)
    {
    case NotStarted:
        return QString(tr("Not Started"));
    case InProgress:
        return QString(tr("In Progress"));
    case Ended:
        return QString(tr("Ended"));
    case Postponed:
        return QString(tr("Postponed"));
    case Waiting:
        return QString(tr("Waiting"));
    default:
        Q_ASSERT(0);
    }
}

QString Activity::getTypeString (Activity::Type value)
{
    return Activity::staticMetaObject.enumerator(
                Activity::staticMetaObject.indexOfEnumerator("Type")).
                valueToKey(value);
}

QString Activity::getPriorityString (Activity::Priority value)
{
    return Activity::staticMetaObject.enumerator(
                Activity::staticMetaObject.indexOfEnumerator("Priority")).
                valueToKey(value);
}
