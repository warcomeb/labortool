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

#ifndef ACTIVITYNOTEDIALOG_H
#define ACTIVITYNOTEDIALOG_H

#include "activitynote.h"

#include <QDialog>

namespace Ui {
class ActivityNoteDialog;
}

class ActivityNoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActivityNoteDialog(QWidget *parent = 0);
    ~ActivityNoteDialog();

    typedef enum
    {
        Add,
        Edit,
        View,
    } DialogType;

    void setOpenType (DialogType type);
    void setSelectedActivityNote (ActivityNote * note);

    ActivityNote* getSavedActivityNote();

    void setOwners (Activity* activity, Employee* const author);

private slots:
    void apply();
    void noApply();

private:
    Ui::ActivityNoteDialog *ui;

    DialogType m_openType;

    ActivityNote * m_activityNote;

    Activity * m_activity;
    Employee * m_author;

    void setupDialog ();
    void saveValues ();
};

#endif // ACTIVITYNOTEDIALOG_H
