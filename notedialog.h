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

#ifndef NOTEDIALOG_H
#define NOTEDIALOG_H

#include "note.h"

#include <QDialog>

namespace Ui {
class NoteDialog;
}

class NoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NoteDialog(QWidget *parent = 0);
    ~NoteDialog();

    typedef enum
    {
        Add,
        Edit,
//        View,
    } DialogType;

    void setOpenType (DialogType type);
    void setParentType (Note::ParentType type);

    void setSelectedNote (Note * note, Employee * const author);
    void prepareNewNote (uint parentId, Employee* const author);

    Note* getSavedNote();

private slots:
    void apply();
    void noApply();

private:
    Ui::NoteDialog *ui;

    DialogType m_openType;

    Note * m_note;

    uint m_parentId;
    Note::ParentType m_parentType;
    Employee * m_author;

    void setupDialog ();
    void saveValues ();

    void fillNoteField();
};

#endif // NOTEDIALOG_H
