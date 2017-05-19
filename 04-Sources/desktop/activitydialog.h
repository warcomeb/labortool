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

#ifndef ACTIVITYDIALOG_H
#define ACTIVITYDIALOG_H

#include <QDialog>

#include <QVector>

#include <QStandardItemModel>
#include <QItemSelection>

#include "activity.h"

#include "employee.h"

#include "note.h"

namespace Ui {
class ActivityDialog;
}

class ActivityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActivityDialog(QWidget *parent = 0);
    ~ActivityDialog();

    typedef enum
    {
        Add,
        Edit,
        View,
        Delete,
    } DialogType;

    void setOpenType (DialogType type);

    void setSelectedActivity (Activity * activity,
                              QVector<Employee *> employeesList,
                              QVector<Note *> notesList);
    void prepareNewActivity (QVector<Employee*> employeesList);

    void setLoggedUserRole(Employee::SystemRole systemRole = Employee::User,
                           Employee::Role role = Employee::Student);

    Activity* getSavedActivity ();

    /**
     * This function must be used only to update an opened ActivityDialog.
     * @brief updateNotesList
     * @param notesList
     */
    void updateNotesList (QVector<Note *> notesList);

    void translateUi();

signals:
    void deleteNoteButton(uint activityNoteId);
    void editNoteButton(uint activityNoteId);
    void addNoteButton(uint activityId);

private slots:
    void addNote();
    void editNote();
    void deleteNote();

    void apply();
    void noApply();

    void selectionChangedNotesTable(const QItemSelection & sel,const QItemSelection & des);

    void keyPressEvent(QKeyEvent *e);

private:
    Ui::ActivityDialog *ui;

    DialogType m_openType;

    Activity * m_activity;

    /* Note table models */
    QStandardItemModel * m_noteModel;
    uint m_noteSelected;

    QVector<Employee *> m_employeesList;
    QVector<Note *> m_notesList;

    Employee::Role m_loggedUserRole;
    Employee::SystemRole m_loggedUserSystemRole;

    void fillCombobox ();

    void setupActivityField ();
    void fillActivityFields ();
    void fillEmployeeField ();

    void updateEmployeesList ();
    void updateNotesList ();

    void updateNotesTab();
    void clearNotesTab();

    void saveValues ();
};

#endif // ACTIVITYDIALOG_H
