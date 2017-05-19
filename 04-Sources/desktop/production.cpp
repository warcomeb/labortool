/******************************************************************************
 * LabOrTool - Laboratory Organization Tool
 * Copyright (C) 2014-2015 Marco Giammarini
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

#include "production.h"

#include <QDebug>
#include <QMetaEnum>

Production::Production(QString boardName):
    m_assignedEmployee(0)
{
    m_boardName = boardName;
    m_quantity = 0;
}

Production::Production():
    m_assignedEmployee(0)
{
}

void Production::setId (uint id)
{
    m_id = id;
}

void Production::setBoardName (QString boardName)
{
    m_boardName = boardName;
}

void Production::setQuantity (uint quantity)
{
    m_quantity = quantity;
}

void Production::setDescription (QString description)
{
    m_description =  description;
}

void Production::setWorkCode (QString code)
{
    m_workCode = code;
}

void Production::setOutputCode (QString code)
{
    m_outputCode = code;
}

void Production::setEmployee (uint employee)
{
    m_assignedEmployee = employee;
}

void Production::setStatus (Status status)
{
    m_status = status;
}

void Production::setDeadline (QDate deadline)
{
    m_deadline = deadline;
}

void Production::setDeadline (QString deadline)
{
    m_deadline = QDate::fromString(deadline,"yyyy-MM-dd");
}

void Production::setStatus (QString status)
{
    qDebug() << "Production::setStatus()";
    QByteArray bytearray = status.toLocal8Bit();
    qDebug() << "Production::setStatus() - string value" << status;

    int value = Production::staticMetaObject.enumerator(
                 Production::staticMetaObject.indexOfEnumerator("Status")).
                 keysToValue(bytearray.data());

    qDebug() << "Production::setStatus() - value" << value;
    m_status = static_cast<Production::Status>(value);
}

QString Production::getStatusString (Status value)
{
    return Production::staticMetaObject.enumerator(
                Production::staticMetaObject.indexOfEnumerator("Status")).
                valueToKey(value);
}

QString Production::getFormattedStatusString (Production::Status value)
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

void Production::setActivityId (uint activityId)
{
    m_activityId = activityId;
}
