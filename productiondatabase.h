/******************************************************************************
 * LabOrTool - Laboratory Organization Tool
 * Copyright (C) 2014-2015 Marco Giammarini
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

#ifndef PRODUCTIONDATABASE_H
#define PRODUCTIONDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QDebug>
#include <QString>

#include "production.h"


class ProductionDatabase
{
public:
    ProductionDatabase(QSqlDatabase * db);

    bool addProduction (Production* production);
    bool updateProduction (Production* production);
    bool getProduction (int id, Production* production);

//    bool addProductionNote (ProductionNote *note);
//    bool getNote (int id, ProductionNote *note);
//    bool updateNote (ProductionNote *note);
//    bool deleteNote (int id);
//    QVector< ProductionNote > getNotes (uint productionId);

    QVector<Production*> searchProductions (QStringList searchParams);

private:

    QSqlDatabase * m_database;
};

#endif // PRODUCTIONDATABASE_H
