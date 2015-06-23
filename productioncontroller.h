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

#ifndef PRODUCTIONCONTROLLER_H
#define PRODUCTIONCONTROLLER_H

#include <QVector>
#include <QSqlDatabase>

#include "employee.h"

#include "production.h"
#include "productiondialog.h"
#include "productiondatabase.h"

#include "notedatabase.h"
#include "notedialog.h"


class ProductionController: public QObject
{
    Q_OBJECT

public:
    ProductionController(QSqlDatabase* db);

    void openAddProductionDialog (QVector<Employee*> employeesList);
    void openEditProductionDialog (uint productionId, QVector<Employee*> employeesList);
    void openViewProductionDialog (uint productionId, QVector<Employee*> employeesList);
    void openDeleteProductionDialog (uint productionId);

    QVector<Production*> getProductionsList (QStringList searchParams);

    void updateLoggedUser(Employee * const employee);

signals:
    void updatedProductionsList(QStringList searchParams);

public slots:
    void openEditNoteProductionDialog (uint productionNoteId);
    void openDeleteNoteProductionDialog (uint productionNoteId);
    void openAddNoteProductionDialog (uint productionId);

private:

    /* View panel */
    ProductionDialog * m_productionDialog;

    /* Note pannel */
    NoteDialog * m_noteDialog;

    /* Productions list */
    QVector<Production> m_activities;

    /* Production wrapper for database */
    ProductionDatabase * m_databaseWrapper;
    NoteDatabase * m_databaseNoteWrapper;
    QSqlDatabase * m_database;

    /* Logged user */
    Employee* m_loggedUser;
};

#endif // PRODUCTIONCONTROLLER_H
