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

#include "note.h"

Note::Note()
{
}

void Note::setId (uint id)
{
    m_id = id;
}

void Note::setParentId (uint id)
{
    m_parentId = id;
}

void Note::setCreationInformation (Employee* const author, QDateTime date)
{
    m_creationEmployee = author->getId();
    m_creationDate = date;
}

void Note::setCreationInformation (Employee* const author, QString date)
{
    m_creationEmployee = author->getId();
    m_creationDate = QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss");
}

void Note::setCreationInformation (uint authorId, QDateTime date)
{
    m_creationEmployee = authorId;
    m_creationDate = date;
}

void Note::setCreationInformation (uint authorId, QString date)
{
    m_creationEmployee = authorId;
    m_creationDate = QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss");
}


void Note::setModificationInformation (Employee* const author, QDateTime date)
{
    m_modificationEmployee = author->getId();
    m_modificationDate = date;
}

void Note::setModificationInformation (Employee* const author, QString date)
{
    m_modificationEmployee = author->getId();
    m_modificationDate = QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss");
}

void Note::setModificationInformation (uint authorId, QDateTime date)
{
    m_modificationEmployee = authorId;
    m_modificationDate = date;
}

void Note::setModificationInformation (uint authorId, QString date)
{
    m_modificationEmployee = authorId;
    m_modificationDate = QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss");
}
void Note::setText(QString text)
{
    m_text = text;
}
