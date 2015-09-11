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

#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QObject>

#include <QString>
#include <QDate>

class Production : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_PROPERTY(Status status READ getStatus WRITE setStatus)

public:
    Production(QString boardName);
    Production();

    typedef enum
    {
        NotStarted,
        InProgress,
        Ended,
        Postponed,
        Waiting,
    } Status;

    uint getId () const { return m_id; }

    QString getBoardName () const { return m_boardName; }
    QString getDescription () const { return m_description; }
    QString getWorkCode () const { return m_workCode; }
    uint getQuantity () const { return m_quantity; }
    QString getOutputCode () const { return m_outputCode; }

    uint getEmployee () const { return m_assignedEmployee; }

    Status getStatus () const { return m_status; }
    QDate getDeadline () const { return m_deadline; }

    uint getActivityId () const { return m_activityId; }

    void setId (uint id);

    void setBoardName (QString title);
    void setDescription (QString description);
    void setWorkCode (QString code);
    void setQuantity (uint quantity);

    void setOutputCode (QString code);

    void setDeadline (QDate deadline);
    void setDeadline (QString deadline);

    void setEmployee (uint employee);

    void setStatus (Status status);
    void setStatus (QString status);

    static QString getStatusString (Status value);

    void setActivityId (uint activityId);

private:
    uint m_id;

    QString m_boardName;
    QString m_description;
    QString m_workCode;
    uint m_quantity;

    QString m_outputCode;

    QDate m_deadline;

    uint m_assignedEmployee;

    Status m_status;

    uint m_activityId;
};

#endif // PRODUCTION_H
