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
        DialogType_Add,
        DialogType_Edit,
        DialogType_View,
        DialogType_Delete,
    } DialogType;

    void setOpenType (DialogType type);

    void setSelectedActivity (Activity * activity,
                              QVector<QVector<QString> > employeesList,
                              QVector<QVector<QString> > notesList);
    void prepareNewActivity (QVector<QVector<QString> > employeesList);

    Activity* getSavedActivity ();

signals:
    void deleteNoteButton(uint activityNoteId);
    void editNoteButton(uint activityNoteId);

private slots:
    void editNote();
    void deleteNote();

    void apply();
    void noApply();

    void selectionChangedNotesTable(const QItemSelection & sel,const QItemSelection & des);

private:
    Ui::ActivityDialog *ui;

    DialogType m_openType;

    Activity * m_activity;

    /* Note table models */
    QStandardItemModel * m_noteModel;
    uint m_noteSelected;

    QVector<QVector<QString> > m_employeesList;
    QVector<QVector<QString> > m_notesList;

    void fillCombobox ();

    void setupActivityField ();
    void fillActivityFields ();
    void fillEmployeeField ();

    void updateEmployeesList ();
    void updateNotesList ();

    void saveValues ();
};

#endif // ACTIVITYDIALOG_H
