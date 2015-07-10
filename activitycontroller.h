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

#ifndef ACTIVITYCONTROLLER_H
#define ACTIVITYCONTROLLER_H

#include <QVector>
#include <QSqlDatabase>

#include "employee.h"

#include "activity.h"
#include "activitydialog.h"
#include "activitydatabase.h"

#include "notedatabase.h"
#include "notedialog.h"

class ActivityController: public QObject
{
    Q_OBJECT

public:
    ActivityController(QSqlDatabase* db);
    ~ActivityController();

    void openAddActivityDialog (QVector<Employee*> employeesList);
    void openEditActivityDialog (uint activityId, QVector<Employee*> employeesList);
    void openViewActivityDialog (uint activityId, QVector<Employee*> employeesList);
    void openDeleteActivityDialog (uint activityId);

    QVector<Activity *> getActivitiesList(QStringList searchParams);

    void updateLoggedUser(Employee * const employee);

signals:
    void updatedActivitiesList(QStringList searchParams);

public slots:
    void openEditNoteActivityDialog (uint activityNoteId);
    void openDeleteNoteActivityDialog (uint activityNoteId);
    void openAddNoteActivityDialog (uint activityId);

private:

    /* View panel */
    ActivityDialog * m_activityDialog;

    /* Activity note pannel */
    NoteDialog * m_noteDialog;

    /* Activities list */
    QVector<Activity> m_activities;

    /* Activity wrapper for database */
    ActivityDatabase * m_databaseWrapper;
    NoteDatabase * m_databaseNoteWrapper;
    QSqlDatabase * m_database;

    /* Logged user */
    Employee* m_loggedUser;
};

#endif // ACTIVITYCONTROLLER_H
