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

#include "notedatabase.h"

#include <QVariant>
#include <QSqlError>

NoteDatabase::NoteDatabase(QSqlDatabase *db)
{
    m_database = db;
}

bool NoteDatabase::addNote (Note* note)
{
    qDebug() << "NoteDatabase::addNote()";

    QSqlQuery query(*m_database);
    QString queryString = "INSERT INTO note "
                          "(NoteParentId, NoteParentType, NoteText, "
                          "NoteEmployeeCreation, NoteDateCreation, "
                          "NoteEmployeeModification, NoteDateModification) "
                          "VALUES (?, ?, ?, ?, ?, ?, ?)";

    query.prepare(queryString);
    query.bindValue(0,note->getParentId());
    query.bindValue(1,Note::getParentTypeString(note->getParentType()));
    query.bindValue(2,note->getText());
    query.bindValue(3,note->getCreationEmployee());
    query.bindValue(4,note->getCreationDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(5,note->getModificationEmployee());
    query.bindValue(6,note->getModificationDate().toString("yyyy-MM-dd hh:mm:ss"));

    qDebug() << "NoteDatabase::addNote() - " << query.lastQuery();

    if (query.exec())
    {
        qDebug() << "NoteDatabase::addNote() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "NoteDatabase::addNote() - "<< query.lastError();
        return false;
    }
}

bool NoteDatabase::getNote (int id, Note *note)
{
    qDebug() << "NoteDatabase::getNote()";

    QString queryString = "SELECT * FROM note WHERE NoteId='" +
            QString::number(id) + "'";

    qDebug() << "NoteDatabase::getNote() - Final search string: " << queryString;
    QSqlQuery query( queryString, *m_database);

    if (query.size() != 1)
    {
        qDebug() << "NoteDatabase::getNote() - database problems!";
        return false;
    }

    /* Read record! */
    qDebug() << "NoteDatabase::getNote() - read record";
    query.next();

    note->setId(id);
    note->setParentId(query.value(1).toString().toUInt());
    note->setParentType(query.value(2).toString()); /* TODO */
    note->setText(query.value(3).toString());
    note->setCreationInformation(query.value(4).toString().toUInt(),
                                 query.value(6).toString());
    note->setModificationInformation(query.value(5).toString().toUInt(),
                                     query.value(7).toString());

    qDebug() << "NoteDatabase::getNote() - note" << id;
    return true;
}

bool NoteDatabase::updateNote (Note *note)
{
    qDebug() << "NoteDatabase::updateNote()";

    QSqlQuery query(*m_database);
    QString queryString = "UPDATE note SET "
            "NoteText=:text ,"
            "NoteEmployeeModification=:modauthor ,"
            "NoteDateModification=:moddate "
            "WHERE NoteId=:rowid";

    query.prepare(queryString);
    query.bindValue(":text",note->getText());
    query.bindValue(":modauthor",QString::number(note->getModificationEmployee()));
    query.bindValue(":moddate",note->getModificationDate().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":rowid",QString::number(note->getId()));

    qDebug() << "NoteDatabase::updateNote() - Bound Value 0 " << query.boundValue(0);
    qDebug() << "NoteDatabase::updateNote() - Bound Value 1 " << query.boundValue(1);
    qDebug() << "NoteDatabase::updateNote() - Bound Value 2 " << query.boundValue(2);
    qDebug() << "NoteDatabase::updateNote() - Bound Value 3 " << query.boundValue(3);

    if (query.exec())
    {
        qDebug() << "NoteDatabase::updateNote() - " << query.lastQuery();
        qDebug() << "NoteDatabase::updateNote() - " << query.lastError();
        qDebug() << "NoteDatabase::updateNote() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "NoteDatabase::updateNote() - " << query.lastQuery();
        qDebug() << "NoteDatabase::updateNote() - " << query.lastError();
        return false;
    }
}

bool NoteDatabase::deleteNote (int id)
{
    qDebug() << "NoteDatabase::deleteNote()";

    QSqlQuery query(*m_database);
    QString queryString = "DELETE FROM note "
            "WHERE NoteId=:rowid";

    query.prepare(queryString);
    query.bindValue(":rowid",QString::number(id));

    qDebug() << "NoteDatabase::deleteNote() - Bound Value 0 " << query.boundValue(0);

    if (query.exec())
    {
        qDebug() << "NoteDatabase::deleteNote() - " << query.lastQuery();
        qDebug() << "NoteDatabase::deleteNote() - " << query.lastError();
        qDebug() << "NoteDatabase::deleteNote() - Query successful";
        return true;
    }
    else
    {
        qDebug() << "NoteDatabase::deleteNote() - " << query.lastQuery();
        qDebug() << "NoteDatabase::deleteNote() - " << query.lastError();
        return false;
    }
}

QVector<Note*>
NoteDatabase::getNotes(uint parentId, Note::ParentType type)
{
    qDebug() << "NoteDatabase::getNotes()";

    QVector<Note*> notesList;

    QString queryString = "SELECT * FROM note WHERE (NoteParentId='" +
            QString::number(parentId) + "' AND NoteParentType='" +
            Note::getParentTypeString(type)+ "') ORDER BY NoteDateCreation DESC";

    qDebug() << "NoteDatabase::getNotes() - Final search string: " << queryString;

    QSqlQuery query( queryString, *m_database);
    while (query.next())
    {
        Note * note = new Note;
        note->setId(query.value(0).toUInt()); // Id
        note->setParentId(query.value(1).toUInt()); // ParentId
        note->setParentType(static_cast<Note::ParentType>(query.value(2).toUInt())); // ParentType
        note->setText(query.value(3).toString()); // Text
        note->setCreationInformation(query.value(4).toUInt(),
                                     query.value(6).toDateTime()); // EmployeeCreation,DateCreation
        note->setModificationInformation(query.value(5).toUInt(),
                                         query.value(7).toDateTime()); // EmployeeModification,DateModification


        qDebug() << "NoteDatabase::getNotes() - Result query" << note->toString();
        notesList.append(note);
    }
    return notesList;
}
