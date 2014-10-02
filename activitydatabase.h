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

#ifndef ACTIVITYDATABASE_H
#define ACTIVITYDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QDebug>
#include <QString>

#include "activity.h"

class ActivityDatabase
{
public:
    ActivityDatabase(QSqlDatabase * db);

    bool addActivity (Activity* activity);

    QVector< QVector< QString > > searchActivities(QStringList searchParams);


private:

    QSqlDatabase * m_database;
};

#endif // ACTIVITYDATABASE_H
