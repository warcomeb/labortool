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

    m_databaseWrapper = new ActivityDatabase (m_database);
}

void ActivityController::openAddActivityDialog (QVector<QVector<QString> > employeesList)
{
    qDebug() << "ActivityController::openAddActivityDialog()";

    m_activityDialog->setOpenType(ActivityDialog::DialogType_Add);
    m_activityDialog->updateEmployeesList(employeesList);
    m_activityDialog->exec();

    Activity * activity = m_activityDialog->getSavedActivity();
    if (activity)
    {
        if (m_databaseWrapper->addActivity(activity))
        {
            qDebug() << "ActivityController::openAddActivityDialog() - Add activities successful";
            QStringList searchParams;
            searchParams << "Status=NotStarted|InProgress|Waiting";
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
    m_activityDialog->setOpenType(ActivityDialog::DialogType_View);
    m_activityDialog->exec();

    /* TODO */
}

void ActivityController::openEditActivityDialog (uint activityId, QVector<QVector<QString> > employeesList)
{
    m_activityDialog->setOpenType(ActivityDialog::DialogType_Edit);
    m_activityDialog->exec();

    /* TODO */
}
