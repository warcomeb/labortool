
/******************************************************************************
 * LabOrTool - Laboratory Organization Tool
 * Copyright (C) 2015 Marco Giammarini
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

#include "productioncontroller.h"

#include <QDebug>
#include <QMessageBox>

#define PRODUCTION_TAG      "[Production]"

ProductionController::ProductionController(QSqlDatabase *db)
{
    m_database = db;

    m_productionDialog = new ProductionDialog;
    m_noteDialog = new NoteDialog;

    m_databaseWrapper = new ProductionDatabase (m_database);
    m_databaseNoteWrapper = new NoteDatabase (m_database);

    m_databaseActivityWrapper = new ActivityDatabase (m_database);
}

ProductionController::~ProductionController()
{
    if (m_productionDialog != 0)
        delete m_productionDialog;

    if (m_noteDialog != 0)
        delete m_noteDialog;
}

void ProductionController::translateUi()
{
    m_productionDialog->translateUi();
    m_noteDialog->translateUi();
}

void ProductionController::openAddProductionDialog (QVector<Employee*> employeesList)
{
    qDebug() << "ProductionController::openAddProductionDialog()";

    m_productionDialog->setOpenType(ProductionDialog::Add);
    m_productionDialog->prepareNewProduction(employeesList);
    m_productionDialog->exec();

    Production * production = m_productionDialog->getSavedProduction();
    if (production)
    {
        if (m_databaseWrapper->addProduction(production))
        {
            // create a new activity bounded with production
            Activity* activity = new Activity;
            convertProductionToActivity(production,activity);
            if (m_databaseActivityWrapper->addActivity(activity))
            {
                production->setActivityId(activity->getId());
                m_databaseWrapper->updateProduction(production);
            }

            if (activity) delete activity;

            qDebug() << "ProductionController::openAddProductionDialog() - Add production successful";
            QStringList searchParams;
            searchParams << "Status$NotStarted|InProgress|Waiting";
            emit updatedProductionsList(searchParams);
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "ProductionController::openAddActivityDialog() - Add porduction error!";
            QMessageBox::warning(0, tr("Add Production Error"),
                                 tr("The production has not been added! Database Error!"));
        }
    }

    delete production;
}

void ProductionController::openViewProductionDialog (uint productionId, QVector<Employee*> employeesList)
{
    qDebug() << "ProductionController::openViewProductionDialog()";

    Production * production = new Production;
    if (!m_databaseWrapper->getProduction(productionId,production))
    {
        QMessageBox::warning(0, tr("View Production Error"),
                             tr("The production can not be displayed! Database Error!"));
        qDebug() << "ActivityController::openViewProductionDialog() - Database Error!";

        delete production;
        return;
    }

    QVector<Note*> notesList = m_databaseNoteWrapper->getNotes(productionId,Note::Production);

    m_productionDialog->setOpenType(ProductionDialog::View);
    m_productionDialog->setSelectedProduction(production,employeesList,notesList);
    m_productionDialog->exec();

    delete production;
}

void ProductionController::openEditProductionDialog (uint productionId, QVector<Employee*> employeesList)
{
    qDebug() << "ProductionController::openEditProductionDialog()";

    // Add connection for dialog!
    connect(m_productionDialog,SIGNAL(editNoteButton(uint)),
            this,SLOT(openEditNoteProductionDialog(uint)));
    connect(m_productionDialog,SIGNAL(deleteNoteButton(uint)),
            this,SLOT(openDeleteNoteProductionDialog(uint)));
    connect(m_productionDialog,SIGNAL(addNoteButton(uint)),
            this,SLOT(openAddNoteProductionDialog(uint)));

    Production * production = new Production;
    if (!m_databaseWrapper->getProduction(productionId,production))
    {
        QMessageBox::warning(0, tr("Edit Production Error"),
                             tr("The production can not be edited! Database Error!"));
        qDebug() << "ProductionController::openEditProductionDialog() - Database Error!";
        delete production;
        return;
    }

    QVector<Note*> notesList = m_databaseNoteWrapper->getNotes(productionId,Note::Production);

    m_productionDialog->setOpenType(ProductionDialog::Edit);
    m_productionDialog->setSelectedProduction(production,employeesList,notesList);

    m_productionDialog->exec();

    production = m_productionDialog->getSavedProduction();
    if (production)
    {
        if (m_databaseWrapper->updateProduction(production))
        {
            Activity* activity = new Activity;
            m_databaseActivityWrapper->getActivity(production->getActivityId(),activity);
            updateActivityFromProduction(production,activity);

            m_databaseActivityWrapper->updateActivity(activity);

            qDebug() << "ProductionController::openEditProductionDialog() - Update production successful";
            QStringList searchParams;
            searchParams << "Status$NotStarted|InProgress|Waiting";
            emit updatedProductionsList(searchParams);
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "ProductionController::openEditProductionDialog() - Update production error!";
            QMessageBox::warning(0, tr("Update Production Error"),
                                 tr("The production has not been updated! Database Error!"));
        }
    }

    delete production;
}

void ProductionController::openDeleteProductionDialog (uint productionId)
{
    qDebug() << "ProductionController::openDeleteProductionDialog()";

    if (productionId == 0)
    {
        /* Warning message!!! */
        QMessageBox::warning(0, tr("Delete Error"),
                              tr("You must select a production!"));
            qDebug() << "ProductionController::openDeleteProductionDialog() - Production not selected!";
        return;
    }

    Production * production = new Production;
    if (!m_databaseWrapper->getProduction(productionId,production))
    {
        /* Warning message!!! */
        QMessageBox::critical(0, tr("Delete Error"),
                             tr("The production can not be deleted! Database Error!"));
            qDebug() << "ProductionController::openDeleteProductionDialog() - Error!";
        return;
    }

    Q_ASSERT((m_loggedUser != 0) && (m_loggedUser->getSystemRole() == Employee::Administrator));

    QMessageBox::StandardButton reply = QMessageBox::question(m_productionDialog,
                                            tr("Delete Production"),
                                            tr("Are you sure you want delete this production?"),
                                            QMessageBox::Yes | QMessageBox::No,
                                            QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        qDebug() << "ProductionController::openDeleteProductionDialog() - User want delete activity" << productionId;
        uint activityId = production->getActivityId();
        if (m_databaseWrapper->deleteProduction(productionId))
        {
            m_databaseActivityWrapper->deleteActivity(activityId);

            qDebug() << "ProductionController::openDeleteProductionDialog() - production deleted" << productionId;
            QMessageBox::warning(0, tr("Delete Production"),
                                  tr("The production has been deleted!"));

            QStringList searchParams;
            searchParams << "Status$NotStarted|InProgress|Waiting";
            emit updatedProductionsList(searchParams);
        }
        else
        {
            qDebug() << "ProductionController::openDeleteProductionDialog() - Delete activity error!";
            QMessageBox::critical(0, tr("Delete Error"),
                                  tr("The production has not been deleted! Database Error!"));
        }
    }

    delete production;
}

void ProductionController::openAddNoteProductionDialog (uint productionId)
{
    qDebug() << "ProductionController::openAddNoteProductionDialog()";

    Production * production = new Production;
    if (!m_databaseWrapper->getProduction(productionId,production))
    {
        /* Warning message!!! */
        QMessageBox::warning(0, tr("Add Production Note Error"),
                             tr("You must select a production!"));
            qDebug() << "ProductionController::openAddNoteProductionDialog() - Exit!";
        return;
    }

    Q_ASSERT(m_loggedUser != 0);

    m_noteDialog->setOpenType(NoteDialog::Add);
    m_noteDialog->setParentType(Note::Production);
    m_noteDialog->prepareNewNote(production->getId(),m_loggedUser);
    m_noteDialog->exec();

    Note* note = m_noteDialog->getSavedNote();
    if (note)
    {
        qDebug() << "ProductionController::openAddNoteProductionDialog() - Note not empty";
        if (m_databaseNoteWrapper->addNote(note))
        {
            qDebug() << "ProductionController::openAddNoteProductionDialog() - Add note successful";
            if (sender() == m_productionDialog)
            {
                QVector<Note*> notesList = m_databaseNoteWrapper->getNotes(note->getParentId(),Note::Production);
                m_productionDialog->updateNotesList(notesList);
            }
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "ProductionController::openAddNoteProductionDialog() - Add production note error!";
            QMessageBox::warning(0, tr("Add Note Error"),
                                 tr("The note has not been added! Database Error!"));
        }
    }
    qDebug() << "ProductionController::openAddNoteActivityDialog() - Exit!";
}

void ProductionController::openEditNoteProductionDialog (uint productionNoteId)
{
    qDebug() << "ProductionController::openEditNoteProductionDialog()";

    if (productionNoteId == 0)
    {
        /* Warning message!!! */
        QMessageBox::warning(0, tr("Edit Note Error"),
                             tr("You must select a note!"));
            qDebug() << "ProductionController::openEditNoteProductionDialog() - Note not selected!";
        return;
    }

    Note * note = new Note;
    if (!m_databaseNoteWrapper->getNote(productionNoteId,note))
    {
        /* Warning message!!! */
        QMessageBox::critical(0, tr("Edit Note Error"),
                             tr("The note can not be edited! Database Error!"));
            qDebug() << "ProductionController::openEditNoteProductionDialog() - Error!";
        return;
    }

    Q_ASSERT(m_loggedUser != 0);

    m_noteDialog->setOpenType(NoteDialog::Edit);
    m_noteDialog->setSelectedNote(note,m_loggedUser);
    m_noteDialog->exec();

    note = m_noteDialog->getSavedNote();
    if (note)
    {
        if (m_databaseNoteWrapper->updateNote(note))
        {
            qDebug() << "ProductionController::openEditNoteActivityDialog() - Update activity note successful";
            QVector<Note*> notesList = m_databaseNoteWrapper->getNotes(note->getParentId(),Note::Production);
            m_productionDialog->updateNotesList(notesList);
        }
        else
        {
            /* Warning message!!! */
            qDebug() << "ProductionController::openEditNoteProductionDialog() - Update note error!";
            QMessageBox::warning(0, tr("Update Note Error"),
                                 tr("The note has not been updated! Database Error!"));
        }

        delete note;
    }
}

void ProductionController::openDeleteNoteProductionDialog (uint productionNoteId)
{
    qDebug() << "ProductionController::openDeleteNoteProductionDialog()";

    if (productionNoteId == 0)
    {
        /* Warning message!!! */
        QMessageBox::warning(0, tr("Delete Note Error"),
                              tr("You must select a note!"));
            qDebug() << "ProductionController::openDeleteNoteProductionDialog() - Note not selected!";
        return;
    }

    Note * note = new Note;
    if (!m_databaseNoteWrapper->getNote(productionNoteId,note))
    {
        /* Warning message!!! */
        QMessageBox::critical(0, tr("Delete Note Error"),
                             tr("The note can not be deleted! Database Error!"));
        qDebug() << "ProductionController::openDeleteNoteProductionDialog() - Error!";
        return;
    }

    Q_ASSERT(m_loggedUser != 0);

    QMessageBox::StandardButton reply = QMessageBox::question(m_productionDialog,
                                            tr("Delete Note"),
                                            tr("Are you sure you want delete this note?"),
                                            QMessageBox::Yes | QMessageBox::No,
                                            QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        qDebug() << "ProductionController::openDeleteNoteProductionDialog() - User want delete note" << productionNoteId;
        if (m_databaseNoteWrapper->deleteNote(productionNoteId))
        {
            qDebug() << "ProductionController::openDeleteNoteProductionDialog() - Note deleted" << productionNoteId;
            QMessageBox::warning(0, tr("Delete Note"),
                                  tr("The note has been deleted!"));

            QVector<Note*> notesList = m_databaseNoteWrapper->getNotes(note->getParentId(),Note::Production);
            m_productionDialog->updateNotesList(notesList);
        }
        else
        {
            qDebug() << "ProductionController::openDeleteNoteProductionDialog() - Delete note error!";
            QMessageBox::critical(0, tr("Delete Note Error"),
                                  tr("The note has not been deleted! Database Error!"));
        }
    }

    delete note;
}

QVector<Production*>
ProductionController::getProductionsList (QStringList searchParams)
{
    qDebug() << "ProductionController::getProductionsList(QStringList)";

    return m_databaseWrapper->searchProductions(searchParams);
}

void ProductionController::updateLoggedUser(Employee* const employee)
{
    qDebug() << "ProductionController::updateLoggedUser()";

    m_loggedUser = employee;

    if (m_loggedUser != 0)
    {
        qDebug() << "ProductionController::updateLoggedUser() - User" << m_loggedUser->getName() << m_loggedUser->getSurname();
        m_productionDialog->setLoggedUserRole(m_loggedUser->getSystemRole(),
                                              m_loggedUser->getRole());
    }
    else
    {
        /* Low level permission! */
        m_productionDialog->setLoggedUserRole();
    }
    qDebug() << "ProductionController::updateLoggedUser() - Exit";
}

void
ProductionController::convertProductionToActivity(Production* production, Activity* activity)
{
    qDebug() << "ProductionController::convertProductionToActivity()";

    QString activityTitle = tr(PRODUCTION_TAG) + " Nr. " + QString::number(production->getQuantity()) +
                                                 " " + production->getBoardName() +
                                                 ", " + production->getOutputCode();
    qDebug() << "ProductionController::convertProductionToActivity() - Title" << activityTitle;
    activity->setTitle(activityTitle);
    activity->setDescription(production->getDescription());
    activity->setWorkCode(production->getWorkCode());

    activity->setEmployee(production->getEmployee());
    activity->setDeadline(production->getDeadline());

    activity->setType(Activity::Production);
    activity->setStatus((Activity::Status)production->getStatus());
    activity->setPriority(Activity::Medium);
}

void
ProductionController::updateActivityFromProduction(Production* production, Activity* activity)
{
    QString activityTitle = tr(PRODUCTION_TAG) + " Nr. " + QString::number(production->getQuantity()) +
                                                 " " + production->getBoardName() +
                                                 ", " + production->getOutputCode();
    qDebug() << "ProductionController::updateActivityFromProduction() - Title" << activityTitle;
    activity->setTitle(activityTitle);
    activity->setDescription(production->getDescription());
    activity->setWorkCode(production->getWorkCode());

    activity->setEmployee(production->getEmployee());
    activity->setDeadline(production->getDeadline());

    activity->setStatus((Activity::Status)production->getStatus());
}
