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

#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QDateTime>

#include "employee.h"

class Note
{
public:
    Note();

    uint getId () const { return m_id; }
    uint getParentId () const { return m_parentId; }

    QString getText() const {return m_text; }

    QDateTime getCreationDate () const { return m_creationDate; }
    uint getCreationEmployee () const { return m_creationEmployee; }

    QDateTime getModificationDate () const { return m_modificationDate; }
    uint getModificationEmployee () const { return m_modificationEmployee; }

    void setId (uint id);
    void setParentId (uint id);

    void setCreationInformation (Employee * const author, QDateTime date);
    void setCreationInformation (Employee* const author, QString date);
    void setCreationInformation (uint authorId, QDateTime date);
    void setCreationInformation (uint authorId, QString date);

    void setModificationInformation (Employee* const author, QDateTime date);
    void setModificationInformation (Employee* const author, QString date);
    void setModificationInformation (uint authorId, QDateTime date);
    void setModificationInformation (uint authorId, QString date);

    void setText(QString text);

private:
    uint m_id;

    uint m_parentId;

    QString m_text;

    uint m_creationEmployee;
    uint m_modificationEmployee;

    QDateTime m_creationDate;
    QDateTime m_modificationDate;
};

#endif // NOTE_H
