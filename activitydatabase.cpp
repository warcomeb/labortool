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

#include "activitydatabase.h"

#include <QVariant>
#include <QSqlError>

#define DB_FIELD_SUFFIX     "Activity"

ActivityDatabase::ActivityDatabase(QSqlDatabase *db)
{
    m_database = db;
}

bool ActivityDatabase::addActivity (Activity* activity)
{
    qDebug() << "ActivityDatabase::addActivity()";

    QSqlQuery query(*m_database);
    QString queryString = "INSERT INTO activity "
                          "(ActivityTitle, ActivityDescription, ActivityWorkCode, "
                          "ActivityDeadline, ActivityEmployee, ActivityStatus, "
                          "ActivityType, ActivityPriority) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

    query.prepare(queryString);
    query.bindValue(0,activity->getTitle());
    query.bindValue(1,activity->getDescription());
    query.bindValue(2,activity->getWorkCode());
    query.bindValue(3,activity->getDeadline().toString("yyyy-MM-dd"));
    query.bindValue(4,activity->getEmployee());
    query.bindValue(5,Activity::getStatusString(activity->getStatus()));
    query.bindValue(6,Activity::getTypeString(activity->getType()));
    query.bindValue(7,Activity::getPriorityString(activity->getPriority()));

    qDebug() << "ActivityDatabase::addActivity() - " << query.lastQuery();

    if (query.exec())
    {
        qDebug() << "ActivityDatabase::addActivity() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "ActivityDatabase::addActivity() - "<< query.lastError();
        return false;
    }
}

QVector< QVector< QString > >
ActivityDatabase::searchActivities(QStringList searchParams)
{
    qDebug() << "ActivityDatabase::searchActivities()";

    QVector<QVector<QString> > activitiesList;

    QString queryString = "SELECT ActivityId, ActivityTitle, ActivityWorkCode, ActivityEmployee, "
                          "ActivityPriority, ActivityStatus, ActivityType, "
                          "ActivityDeadline FROM activity ";

    if (searchParams.size()>0)
    {
        qDebug() << "ActivityDatabase::searchActivities() - Search param list is not empty";

        queryString.append("WHERE ( ");
        for (int i = 0; i < searchParams.size(); ++i)
        {
            qDebug() << "ActivityDatabase::searchActivities() - Param:" << searchParams.at(i);

            if (searchParams.at(i).indexOf('=') != -1)
            {
                QStringList searchParam = searchParams.at(i).split('=');
                if (searchParam.size() == 2)
                {
                    qDebug() << "ActivityDatabase::searchActivities() - Param is correct";
                    queryString.append(DB_FIELD_SUFFIX +
                                       searchParam.at(0) +  "='" +
                                       searchParam.at(1) + "' ");
                }
                else
                {
                    qDebug() << "ActivityDatabase::searchActivities() - Param is not correct";
                    return activitiesList;
                }

            }
            else if (searchParams.at(i).indexOf('$') != -1)
            {
                QStringList searchParam = searchParams.at(i).split('$');
                if (searchParam.size() == 2)
                {
                    qDebug() << "ActivityDatabase::searchActivities() - Param is correct";
                    qDebug() << "ActivityDatabase::searchActivities()" << searchParam;
                    QStringList searchComboParams = searchParam.at(1).split('|');
                    queryString.append("( ");
                    for (int j = 0; j < searchComboParams.size(); ++j)
                    {
                        queryString.append(DB_FIELD_SUFFIX +
                                           searchParam.at(0) +  "='" +
                                           searchComboParams.at(i) + "' ");

                        if (j+1 == searchComboParams.size())
                            queryString.append(") ");
                        else
                            queryString.append("OR ");
                    }
                }
                else
                {
                    qDebug() << "ActivityDatabase::searchActivities() - Param is not correct";
                    return activitiesList;
                }
            }
            else if (searchParams.at(i).indexOf('%') != -1)
            {
                QStringList searchParam = searchParams.at(i).split('%');
                if (searchParam.size() == 2)
                {
                    qDebug() << "ActivityDatabase::searchActivities() - Param is correct";
                    queryString.append(
                        "( ActivityTitle LIKE '%" + searchParam.at(1) + "%' OR " +
                        "ActivityDescription LIKE '%" + searchParam.at(1) + "%') "
                    );
                }
                else
                {
                    qDebug() << "ActivityDatabase::searchActivities() - Param is not correct";
                    return activitiesList;
                }
            }
            else
            {
                qDebug() << "ActivityDatabase::searchActivities() - Param is not correct";
                return activitiesList;
            }

            if (i+1 == searchParams.size())
                queryString.append(") ");
            else
                queryString.append(" AND ");
        }

    }
    queryString.append("ORDER BY ActivityDeadline ASC");

    qDebug() << "ActivityDatabase::searchActivities() - Final search string: " << queryString;

    QSqlQuery query( queryString, *m_database);
    while (query.next())
    {
        QVector<QString> activity;
        activity.append(query.value(0).toString()); // Id
        activity.append(query.value(1).toString()); // Title
        activity.append(query.value(2).toString()); // WorkCode
        activity.append(query.value(3).toString()); // Employee
        activity.append(query.value(4).toString()); // Priority
        activity.append(query.value(5).toString()); // Status
        activity.append(query.value(6).toString()); // Type

        activitiesList.append(activity);
    }

    qDebug() << "ActivityDatabase::searchActivities() - Final list" << activitiesList;
    return activitiesList;
}
