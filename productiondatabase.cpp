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

#include "productiondatabase.h"

#include <QVariant>
#include <QSqlError>

#define DB_FIELD_SUFFIX     "Production"

ProductionDatabase::ProductionDatabase(QSqlDatabase *db)
{
    m_database = db;
}

bool ProductionDatabase::addProduction (Production* production)
{
    qDebug() << "ProductionDatabase::addProduction()";

    QSqlQuery query(*m_database);
    QString queryString = "INSERT INTO production "
                          "(ProductionTitle, ProductionDescription, ProductionWorkCode, "
                          "ProductionOutputCod, ProductionEmployee, ProductionStatus) "
                          "VALUES (?, ?, ?, ?, ?, ?)";

    query.prepare(queryString);
    query.bindValue(0,production->getTitle());
    query.bindValue(1,production->getDescription());
    query.bindValue(2,production->getWorkCode());
    query.bindValue(3,production->getOutputCode());
    query.bindValue(4,production->getEmployee());
    query.bindValue(5,Production::getStatusString(production->getStatus()));

    qDebug() << "ProductionDatabase::addProduction() - " << query.lastQuery();

    if (query.exec())
    {
        qDebug() << "ProductionDatabase::addProduction() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "ProductionDatabase::addProduction() - "<< query.lastError();
        return false;
    }
}

bool ProductionDatabase::getProduction (int id, Production *production)
{
    qDebug() << "ProductionDatabase::getProduction()";

    QString queryString = "SELECT * FROM producttion WHERE ProductionId='" +
            QString::number(id) + "'";

    qDebug() << "ProductionDatabase::getProduction() - Final search string: " << queryString;
    QSqlQuery query( queryString, *m_database);

    if (query.size() != 1)
    {
        qDebug() << "ProductionDatabase::getProduction() - database problems!";
        return false;
    }

    /* Read record! */
    qDebug() << "ProductionDatabase::getProduction() - read record";
    query.next();

    /* TODO */
    production->setId(id);
    production->setTitle(query.value(1).toString());
    production->setDescription(query.value(2).toString());
    production->setWorkCode(query.value(3).toString());
    production->setOutputCode(query.value(4).toString());
    production->setEmployee(query.value(5).toString().toUInt());
    production->setStatus(query.value(6).toString());

    qDebug() << "ProductionDatabase::getProduction() - production" << id <<
                query.value(3).toString() << query.value(1).toString();
    return true;
}
