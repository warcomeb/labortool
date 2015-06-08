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

ProductionController::ProductionController(QSqlDatabase *db)
{
    m_database = db;

    m_productionDialog = new ProductionDialog;
//    m_productionNoteDialog = new ProductionNoteDialog;

    m_databaseWrapper = new ProductionDatabase (m_database);

    connect(m_productionDialog,SIGNAL(editNoteButton(uint)),
            this,SLOT(openEditNoteProductionDialog(uint)));
    connect(m_productionDialog,SIGNAL(deleteNoteButton(uint)),
            this,SLOT(openDeleteNoteProductionDialog(uint)));
    connect(m_productionDialog,SIGNAL(addNoteButton(uint)),
            this,SLOT(openAddNoteProductionDialog(uint)));
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
}

//void ProductionController::openViewActivityDialog (uint activityId, QVector<QVector<QString> > employeesList)
//{
//    qDebug() << "ProductionController::openViewActivityDialog()";

//    Activity * activity = new Activity;
//    if (!m_databaseWrapper->getActivity(activityId,activity))
//    {
//        QMessageBox::warning(0, tr("View Activity Error"),
//                             tr("The activity can not be displayed! Database Error!"));
//        qDebug() << "ActivityController::openViewActivityDialog() - Database Error!";
//        return;
//    }

//    QVector<QVector<QString> > notesList = m_databaseWrapper->getNotes(activityId);

//    m_activityDialog->setOpenType(ActivityDialog::View);
//    m_activityDialog->setSelectedActivity(activity,employeesList,notesList);
//    m_activityDialog->exec();
//}

//void ProductionController::openEditActivityDialog (uint activityId, QVector<QVector<QString> > employeesList)
//{
//    qDebug() << "ProductionController::openEditActivityDialog()";

//    Activity * activity = new Activity;
//    if (!m_databaseWrapper->getActivity(activityId,activity))
//    {
//        QMessageBox::warning(0, tr("Edit Activity Error"),
//                             tr("The activity can not be edited! Database Error!"));
//        qDebug() << "ProductionController::openEditActivityDialog() - Database Error!";
//        return;
//    }

//    QVector<QVector<QString> > notesList = m_databaseWrapper->getNotes(activityId);

//    m_activityDialog->setOpenType(ActivityDialog::Edit);
//    m_activityDialog->setSelectedActivity(activity,employeesList,notesList);

//    m_activityDialog->exec();

//    activity = m_activityDialog->getSavedActivity();
//    if (activity)
//    {
//        if (m_databaseWrapper->updateActivity(activity))
//        {
//            qDebug() << "ProductionController::openEditActivityDialog() - Update activity successful";
//            QStringList searchParams;
//            searchParams << "Status$NotStarted|InProgress|Waiting";
//            emit updatedActivitiesList(searchParams);
//        }
//        else
//        {
//            /* Warning message!!! */
//            qDebug() << "ProductionController::openEditActivityDialog() - Update activity error!";
//            QMessageBox::warning(0, tr("Update Activity Error"),
//                                 tr("The activity has not been updated! Database Error!"));
//        }
//    }
//}

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
