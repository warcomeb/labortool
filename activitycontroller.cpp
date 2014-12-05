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

    connect(m_activityDialog,SIGNAL(editNoteButton(uint)),
            this,SLOT(openEditNoteActivityDialog(uint)));
    connect(m_activityDialog,SIGNAL(deleteNoteButton(uint)),
            this,SLOT(openDeleteNoteActivityDialog(uint)));
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

void ActivityController::openAddNoteActivityDialog (uint activityId)
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

    Q_ASSERT(m_loggedUser != 0);

    m_activityNoteDialog->setOpenType(ActivityNoteDialog::Add);
    m_activityNoteDialog->setOwners(activity,m_loggedUser);
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

void ActivityController::openEditNoteActivityDialog (uint activityNoteId)
{
    qDebug() << "ActivityController::openEditNoteActivityDialog()";

    if (activityNoteId == 0)
    {
        /* Warning message!!! */
        QMessageBox::warning(0, tr("Edit Activity Note Error"),
                             tr("You must select an activity note!"));
            qDebug() << "ActivityController::openEditNoteActivityDialog() - Note not selected!";
        return;
    }

    ActivityNote * note = new ActivityNote;
    if (!m_databaseWrapper->getNote(activityNoteId,note))
    {
        /* Warning message!!! */
        QMessageBox::critical(0, tr("Edit Activity Note Error"),
                             tr("The activity note can not be edited! Database Error!"));
            qDebug() << "ActivityController::openEditNoteActivityDialog() - Error!";
        return;
    }

    Q_ASSERT(m_loggedUser != 0);

    m_activityNoteDialog->setOpenType(ActivityNoteDialog::Edit);
    m_activityNoteDialog->setSelectedActivityNote(note,m_loggedUser);
    m_activityNoteDialog->exec();

    note = m_activityNoteDialog->getSavedActivityNote();
    if (note)
    {
        if (m_databaseWrapper->updateNote(note))
        {
            qDebug() << "ActivityController::openEditNoteActivityDialog() - Update activity note successful";
            QVector<QVector<QString> > notesList = m_databaseWrapper->getNotes(note->getActivityId());
            m_activityDialog->updateNotesList(notesList);
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "ActivityController::openEditNoteActivityDialog() - Update activity note error!";
            QMessageBox::warning(0, tr("Update Activity Note Error"),
                                 tr("The activity note has not been updated! Database Error!"));
        }

        delete note;
    }

}

void ActivityController::openDeleteNoteActivityDialog (uint activityNoteId)
{
    qDebug() << "ActivityController::openDeleteNoteActivityDialog()";

    if (activityNoteId == 0)
    {
        /* Warning message!!! */
        QMessageBox::warning(0, tr("Delete Activity Note Error"),
                              tr("You must select an activity note!"));
            qDebug() << "ActivityController::openDeleteNoteActivityDialog() - Note not selected!";
        return;
    }

    ActivityNote * note = new ActivityNote;
    if (!m_databaseWrapper->getNote(activityNoteId,note))
    {
        /* Warning message!!! */
        QMessageBox::critical(0, tr("Delete Activity Note Error"),
                             tr("The activity note can not be deleted! Database Error!"));
            qDebug() << "ActivityController::openDeleteNoteActivityDialog() - Error!";
        return;
    }

    Q_ASSERT(m_loggedUser != 0);

    QMessageBox::StandardButton reply = QMessageBox::question(m_activityDialog,
                                            tr("Delete Activity Note"),
                                            tr("Are you sure you want delete this note?"),
                                            QMessageBox::Yes | QMessageBox::No,
                                            QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        qDebug() << "ActivityController::openDeleteNoteActivityDialog() - User want delete note" << activityNoteId;
        if (m_databaseWrapper->deleteNote(activityNoteId))
        {
            qDebug() << "ActivityController::openDeleteNoteActivityDialog() - Note deleted" << activityNoteId;
            QMessageBox::warning(0, tr("Delete Activity Note"),
                                  tr("The activity note has been deleted!"));

            QVector<QVector<QString> > notesList = m_databaseWrapper->getNotes(note->getActivityId());
            m_activityDialog->updateNotesList(notesList);
        }
        else
        {
            qDebug() << "ActivityController::openDeleteNoteActivityDialog() - Delete activity note error!";
            QMessageBox::critical(0, tr("Delete Activity Note Error"),
                                  tr("The activity note has not been deleted! Database Error!"));
        }
    }

    delete note;
}

QVector<QVector<QString> >
ActivityController::getActivitiesList (QStringList searchParams)
{
    qDebug() << "ActivityController::getActivitiesList(QStringList)";

    return m_databaseWrapper->searchActivities(searchParams);
}

void ActivityController::updateLoggedUser(Employee* const employee)
{
    qDebug() << "ActivityController::updateLoggedUser()";

    m_loggedUser = employee;
    qDebug() << "ActivityController::updateLoggedUser() - User" << m_loggedUser->getName() << m_loggedUser->getSurname();

    if (m_loggedUser != 0)
    {
        m_activityDialog->setLoggedUserRole(m_loggedUser->getSystemRole(),
                                            m_loggedUser->getRole());
    }
    else
    {
        /* Low level permission! */
        m_activityDialog->setLoggedUserRole();
    }
    qDebug() << "ActivityController::updateLoggedUser() - Exit";
}
