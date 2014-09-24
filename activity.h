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

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>

#include <QVector>
#include <QMap>
#include <QString>
#include <QDate>

#include "activitynote.h"

class Activity : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status Type Priority)
    Q_PROPERTY(Status status READ getStatus WRITE setStatus)
    Q_PROPERTY(Type type READ getType WRITE setType)
    Q_PROPERTY(Priority priority READ getPriority WRITE setPriority)

public:
    Activity(QString title);
    Activity();

    typedef enum
    {
        NotStarted,
        InProgress,
        Ended,
        Postponed,
        Waiting,
    } Status;

    typedef enum
    {
        Board,
        Repair,
        Support,
        Firmware,
        Production,
    } Type;

    typedef enum
    {
        Low,
        Medium,
        High,
        Now,
    } Priority;

    uint getId () const { return m_id; }

    QString getTitle () const { return m_title; }
    QString getDescription () const { return m_description; }
    QString getWorkCode () const { return m_workCode; }

    uint getEmployee () const { return m_assignedEmployee; }
    QDate getDeadline () const { return m_deadline; }

    Type getType () const { return m_type; }
    Status getStatus () const { return m_status; }
    Priority getPriority () const { return m_priority; }

    void setId (uint id);

    void setTitle (QString title);
    void setDescription (QString description);
    void setWorkCode (QString code);

    void setDeadline (QDate deadline);
    void setDeadline (QString deadline);
    void setEmployee (uint employee);

    void setType (Type type);
    void setStatus (Status status);
    void setPriority (Priority priority);

    void setType (QString type);
    void setStatus (QString status);
    void setPriority (QString priority);

    void addNote (ActivityNote* note);
    void deleteNote (ActivityNote* note);
    QVector<ActivityNote*> getNotes ();

    void addAttachment (QString attachment);
    void deleteAttachment (uint attachment);
    QMap<uint,QString> getAttachments ();

    static QString getTypeString (Type value);
    static QString getStatusString (Status value);
    static QString getPriorityString (Priority value);

private:
    uint m_id;

    QString m_title;
    QString m_description;
    QString m_workCode;

    uint m_assignedEmployee;

    QDate m_deadline;

    Status m_status;
    Type m_type;
    Priority m_priority;

    QVector<ActivityNote*> m_notes;

    QMap<uint,QString> m_attachments;
};

#endif // ACTIVITY_H
