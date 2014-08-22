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

#include <QVector>
#include <QMap>
#include <QString>
#include <QDate>

#include "employee.h"
#include "activitynote.h"

class Activity
{
public:
    Activity(QString title);

    typedef enum
    {
        Status_NotStarted,
        Status_InProgress,
        Status_Ended,
        Status_Postponed,
        Status_Waiting,
    } Status;

    typedef enum
    {
        Type_Board,
        Type_Repair,
        Type_Support,
        Type_Firmware,
        Type_Production,
    } Type;

//    typedef enum
//    {
//        Typology_Internal,
//        Typology_Research,
//        Typology_Production,
//    } Typology;


    void setTitle  (QString title);
    QString getTitle ();

    void setDescription  (QString description);
    QString getDescription ();

    void setWorkCode  (QString code);
    QString getWorkCode ();

    void setDeadline (QDate deadline);
    QDate getDeadline ();

    void setEmployee (Employee* employee);
    Employee* getEmployee ();

//    void setTypology (Typology typology);
//    Typology getTypology ();

    void setType (Type type);
    Type getType ();

    void setStatus (Status status);
    Status getStatus ();

    void addNote (ActivityNote* note);
    void deleteNote (ActivityNote* note);
    QVector<ActivityNote*> getNotes ();

    void addAttachment (QString attachment);
    void deleteAttachment (uint attachment);
    QMap<uint,QString> getAttachments ();

    void storeData ();
    void readData ();

private:
    uint m_id;

    QString m_title;
    QString m_description;
    QString m_workCode;

    Employee* m_assignedEmployee;

    Status m_status;
    QDate m_deadline;

//    Typology m_typology;
    Type m_type;

    QVector<ActivityNote*> m_notes;

    QMap<uint,QString> m_attachments;
};

#endif // ACTIVITY_H
