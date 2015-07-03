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

bool ActivityDatabase::getActivity (int id, Activity *activity)
{
    qDebug() << "ActivityDatabase::getActivity()";

    QString queryString = "SELECT * FROM activity WHERE ActivityId='" +
            QString::number(id) + "'";

    qDebug() << "ActivityDatabase::getActivity() - Final search string: " << queryString;
    QSqlQuery query( queryString, *m_database);

    if (query.size() != 1)
    {
        qDebug() << "ActivityDatabase::getActivity() - database problems!";
        return false;
    }

    /* Read record! */
    qDebug() << "ActivityDatabase::getActivity() - read record";
    query.next();

    /* TODO */
    activity->setId(id);
    activity->setTitle(query.value(1).toString());
    activity->setDescription(query.value(2).toString());
    activity->setWorkCode(query.value(3).toString());
    activity->setDeadline(query.value(4).toString());
    activity->setPriority(query.value(5).toString());
    activity->setStatus(query.value(6).toString());
    activity->setType(query.value(7).toString());
    activity->setEmployee(query.value(8).toString().toUInt());

    qDebug() << "ActivityDatabase::getActivity() - activity" << id <<
                query.value(3).toString() << query.value(1).toString();
    return true;
}

bool ActivityDatabase::updateActivity (Activity *activity)
{
    qDebug() << "ActivityDatabase::updateActivity()";

    QSqlQuery query(*m_database);
    QString queryString = "UPDATE activity SET "
            "ActivityTitle=:title ,"
            "ActivityDescription=:desc ,"
            "ActivityWorkCode=:code ,"
            "ActivityDeadline=:deadline ,"
            "ActivityEmployee=:employee ,"
            "ActivityStatus=:status ,"
            "ActivityType=:type ,"
            "ActivityPriority=:priority "
            "WHERE ActivityId=:rowid";

    query.prepare(queryString);
    query.bindValue(":title",activity->getTitle());
    query.bindValue(":desc",activity->getDescription());
    query.bindValue(":code",activity->getWorkCode());
    query.bindValue(":deadline",activity->getDeadline().toString("yyyy-MM-dd"));
    query.bindValue(":employee",QString::number(activity->getEmployee()));
    query.bindValue(":status",QString(Activity::getStatusString(activity->getStatus())));
    query.bindValue(":type",Activity::getTypeString(activity->getType()));
    query.bindValue(":priority",Activity::getPriorityString(activity->getPriority()));
    query.bindValue(":rowid",QString::number(activity->getId()));

    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 0 " << query.boundValue(0);
    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 1 " << query.boundValue(1);
    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 2 " << query.boundValue(2);
    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 3 " << query.boundValue(3);
    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 4 " << query.boundValue(4);
    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 5 " << query.boundValue(5);
    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 6 " << query.boundValue(6);
    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 7 " << query.boundValue(7);
    qDebug() << "ActivityDatabase::updateActivity() - Bound Value 8 " << query.boundValue(8);

    if (query.exec())
    {
        qDebug() << "ActivityDatabase::updateActivity() - " << query.lastQuery();
        qDebug() << "ActivityDatabase::updateActivity() - " << query.lastError();
        qDebug() << "ActivityDatabase::updateActivity() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "ActivityDatabase::updateActivity() - " << query.lastQuery();
        qDebug() << "ActivityDatabase::updateActivity() - " << query.lastError();
        return false;
    }
}

bool ActivityDatabase::deleteActivity (int id)
{
    qDebug() << "ActivityDatabase::deleteActivity()";

    QSqlQuery query(*m_database);
    QString queryString = "DELETE FROM activity "
            "WHERE ActivityId=:rowid";

    query.prepare(queryString);
    query.bindValue(":rowid",QString::number(id));

    qDebug() << "ActivityDatabase::deleteActivity() - Bound Value 0 " << query.boundValue(0);

    if (query.exec())
    {
        qDebug() << "ActivityDatabase::deleteActivity() - " << query.lastQuery();
        qDebug() << "ActivityDatabase::deleteActivity() - " << query.lastError();
        qDebug() << "ActivityDatabase::deleteActivity() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "ActivityDatabase::deleteActivity() - " << query.lastQuery();
        qDebug() << "ActivityDatabase::deleteActivity() - " << query.lastError();
        return false;
    }
}

QVector<Activity *> ActivityDatabase::searchActivities(QStringList searchParams)
{
    qDebug() << "ActivityDatabase::searchActivities()";

    QVector<Activity *> activitiesList;

    QString queryString = "SELECT ActivityId, ActivityTitle, ActivityWorkCode, "
                          "ActivityEmployee, ActivityPriority, ActivityStatus, "
                          "ActivityType, ActivityDeadline FROM activity ";

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
                                           searchComboParams.at(j) + "' ");

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
                        "ActivityDescription LIKE '%" + searchParam.at(1) + "%' OR " +
                        "ActivityWorkCode LIKE '%" + searchParam.at(1) + "%') "
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
        Activity * activity = new Activity;
        activity->setId(query.value(0).toString().toUInt()); // Id
        activity->setTitle(query.value(1).toString()); // Title
        activity->setWorkCode(query.value(2).toString()); // WorkCode
        activity->setEmployee(query.value(3).toString().toUInt()); // Employee
        activity->setPriority(query.value(4).toString()); // Priority
        activity->setStatus(query.value(5).toString()); // Status
        activity->setType(query.value(6).toString()); // Type
        activity->setDeadline(query.value(7).toString()); // Deadline

        activitiesList.append(activity);
    }

    qDebug() << "ActivityDatabase::searchActivities() - Final list" << activitiesList;
    return activitiesList;
}
