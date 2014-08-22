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

#include <QTableView>
#include <QVector>
#include <QSqlDatabase>

#include "activity.h"
#include "activitydialog.h"
#include "activitydatabase.h"

class ActivityController
{
public:
    ActivityController(QTableView * activities, QSqlDatabase* db);

    void openAddActivityDialog ();
    void openEditActivityDialog ();
    void openViewActivityDialog ();

private:

    /* View panel */
    QTableView * m_tableActivities;
    ActivityDialog * m_activityDialog;

    /* Activities list */
    QVector<Activity> m_activities;

    /* Activity wrapper for database */
    ActivityDatabase * m_databaseWrapper;
    QSqlDatabase * m_database;
};

#endif // ACTIVITYCONTROLLER_H
