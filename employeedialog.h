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

#ifndef EMPLOYEEDIALOG_H
#define EMPLOYEEDIALOG_H

#include <QDialog>

#include "employee.h"

namespace Ui {
class EmployeeDialog;
}

class EmployeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeDialog(QWidget *parent = 0);
    ~EmployeeDialog();

    typedef enum
    {
        Add,
        Edit,
        View,
    } DialogType;

    void setOpenType (DialogType type);
    void setSelectedEmployee (Employee * employee);

    Employee* getSavedEmployee ();

    void setLoggedUserRole(Employee::SystemRole systemRole = Employee::User,
                           Employee::Role role = Employee::Student);

private slots:
    void apply();
    void noApply();

private:
    Ui::EmployeeDialog *ui;

    DialogType m_openType;

    Employee * m_employee;

    Employee::Role m_loggedUserRole;
    Employee::SystemRole m_loggedUserSystemRole;

    void fillCombobox ();

    void setupEmployeeField ();
    void fillEmployeeField ();

    void saveValues ();
};

#endif // EMPLOYEEDIALOG_H
