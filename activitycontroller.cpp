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

#include "activitycontroller.h"

#include <QDebug>
#include <QMessageBox>

ActivityController::ActivityController(QSqlDatabase *db)
{
    m_database = db;

    m_activityDialog = new ActivityDialog;
    m_activityNoteDialog = new ActivityNoteDialog;

    m_databaseWrapper = new ActivityDatabase (m_database);
}

void ActivityController::openAddActivityDialog (QVector<QVector<QString> > employeesList)
{
    qDebug() << "ActivityController::openAddActivityDialog()";

    m_activityDialog->setOpenType(ActivityDialog::DialogType_Add);
    m_activityDialog->prepareNewActivity(employeesList);
    m_activityDialog->exec();

    Activity * activity = m_activityDialog->getSavedActivity();
    if (activity)
    {
        if (m_databaseWrapper->addActivity(activity))
        {
            qDebug() << "ActivityController::openAddActivityDialog() - Add activities successful";
            QStringList searchParams;
            searchParams << "Status$NotStarted|InProgress|Waiting";
            emit updatedActivitiesList(searchParams);
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "ActivityController::openAddActivityDialog() - Add activity error!";
            QMessageBox::warning(0, tr("Add Activity Error"),
                                 tr("The activity has not been added! Database Error!"));
        }
    }
}

void ActivityController::openViewActivityDialog (uint activityId, QVector<QVector<QString> > employeesList)
{
    qDebug() << "ActivityController::openViewActivityDialog()";

    Activity * activity = new Activity;
    if (!m_databaseWrapper->getActivity(activityId,activity))
    {
        QMessageBox::warning(0, tr("View Activity Error"),
                             tr("The activity can not be displayed! Database Error!"));
        qDebug() << "ActivityController::openViewActivityDialog() - Database Error!";
        return;
    }

    QVector<QVector<QString> > notesList = m_databaseWrapper->getNotes(activityId);

    m_activityDialog->setOpenType(ActivityDialog::DialogType_View);
    m_activityDialog->setSelectedActivity(activity,employeesList,notesList);
    m_activityDialog->exec();
}

void ActivityController::openEditActivityDialog (uint activityId, QVector<QVector<QString> > employeesList)
{
    qDebug() << "ActivityController::openEditActivityDialog()";

    Activity * activity = new Activity;
    if (!m_databaseWrapper->getActivity(activityId,activity))
    {
        QMessageBox::warning(0, tr("Edit Activity Error"),
                             tr("The activity can not be edited! Database Error!"));
        qDebug() << "ActivityController::openEditActivityDialog() - Database Error!";
        return;
    }

    QVector<QVector<QString> > notesList = m_databaseWrapper->getNotes(activityId);

    m_activityDialog->setOpenType(ActivityDialog::DialogType_Edit);
    m_activityDialog->setSelectedActivity(activity,employeesList,notesList);

    m_activityDialog->exec();

    activity = m_activityDialog->getSavedActivity();
    if (activity)
    {
        if (m_databaseWrapper->updateActivity(activity))
        {
            qDebug() << "ActivityController::openEditActivityDialog() - Update activity successful";
            QStringList searchParams;
            searchParams << "Status$NotStarted|InProgress|Waiting";
            emit updatedActivitiesList(searchParams);
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "ActivityController::openEditActivityDialog() - Update activity error!";
            QMessageBox::warning(0, tr("Update Activity Error"),
                                 tr("The activity has not been updated! Database Error!"));
        }
    }
}

void ActivityController::openAddNoteActivityDialog (uint activityId, Employee* loggedEmployee)
{
    qDebug() << "ActivityController::openAddNoteActivityDialog()";

    Activity * activity = new Activity;
    if (!m_databaseWrapper->getActivity(activityId,activity))
    {
        /* Warning message!!! */
        QMessageBox::critical(0, tr("Add Activity Note Error"),
                             tr("You must select an activity!"));
            qDebug() << "ActivityController::openAddNoteActivityDialog() - Exit!";
        return;
    }

    m_activityNoteDialog->setOpenType(ActivityNoteDialog::Add);
    m_activityNoteDialog->setOwners(activity,loggedEmployee);
    m_activityNoteDialog->exec();

    ActivityNote* note = m_activityNoteDialog->getSavedActivityNote();
    if (note)
    {
        qDebug() << "ActivityController::openAddNoteActivityDialog() - Note not empty";
        if (m_databaseWrapper->addActivityNote(note))
        {
            qDebug() << "ActivityController::openAddNoteActivityDialog() - Add activity note successful";
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "ActivityController::openAddNoteActivityDialog() - Add activity note error!";
            QMessageBox::warning(0, tr("Add Activity Note Error"),
                                 tr("The activity note has not been added! Database Error!"));
        }
    }
    qDebug() << "ActivityController::openAddNoteActivityDialog() - Exit!";
}

QVector<QVector<QString> >
ActivityController::getActivitiesList (QStringList searchParams)
{
    qDebug() << "ActivityController::getActivitiesList(QStringList)";

    return m_databaseWrapper->searchActivities(searchParams);
}
