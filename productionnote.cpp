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

#include "productionnote.h"

ProductionNote::ProductionNote(QString text, Production* production, Employee* author)
{
    setId(0);
    setParentId(production->getId());
    setText(text);

    setCreationInformation(author->getId(),QDateTime::currentDateTime());
    setModificationInformation(author->getId(),QDateTime::currentDateTime());
}

ProductionNote::ProductionNote()
{
    setId(0);
    setText("");
}
