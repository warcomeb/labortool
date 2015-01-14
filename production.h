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

class Production : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_PROPERTY(Status status READ getStatus WRITE setStatus)

public:
    Production(QString title);
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

    QString getTitle () const { return m_title; }
    QString getDescription () const { return m_description; }
    QString getWorkCode () const { return m_workCode; }

    QString getOutputCode () const { return m_outputCode; }

    uint getEmployee () const { return m_assignedEmployee; }

    Status getStatus () const { return m_status; }

    void setId (uint id);

    void setTitle (QString title);
    void setDescription (QString description);
    void setWorkCode (QString code);

    void setOutputCode (QString code);

    void setEmployee (uint employee);

    void setStatus (Status status);
    void setStatus (QString status);

    static QString getStatusString (Status value);

private:
    uint m_id;

    QString m_title;
    QString m_description;
    QString m_workCode;

    QString m_outputCode;

    uint m_assignedEmployee;

    Status m_status;
};

#endif // PRODUCTION_H
