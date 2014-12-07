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

#include "employeedialog.h"
#include "ui_employeedialog.h"

#include <QDebug>
#include <QMessageBox>

#include "metadata.h"

EmployeeDialog::EmployeeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeDialog),
    m_openType(View),
    m_loggedUserRole(Employee::Student), /* Low level permissions */
    m_loggedUserSystemRole(Employee::User)
{
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION) + " - Employee Dialog");

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(noApply()));

    fillCombobox();

    setupEmployeeField();
}

EmployeeDialog::~EmployeeDialog()
{
    if (m_employee)
        delete m_employee;

    delete ui;
}

void EmployeeDialog::fillCombobox ()
{
    ui->roleCombobox->clear();
    ui->roleCombobox->addItem(tr("Coordinator"), Employee::Coordinator);
    ui->roleCombobox->addItem(tr("Senior Designer"), Employee::SeniorDesigner);
    ui->roleCombobox->addItem(tr("Designer"), Employee::Designer);
    ui->roleCombobox->addItem(tr("Technician"), Employee::Technician);
    ui->roleCombobox->addItem(tr("Student"), Employee::Student);

    ui->sysroleCombobox->clear();
    ui->sysroleCombobox->addItem(tr("Administrator"), Employee::Administrator);
    ui->sysroleCombobox->addItem(tr("Editor"), Employee::Editor);
    ui->sysroleCombobox->addItem(tr("User"), Employee::User);

    ui->companyCombobox->clear();
    ui->companyCombobox->addItem(tr("AEA"), Employee::Aea);
    ui->companyCombobox->addItem(tr("General Impianti"), Employee::Gi);
    ui->companyCombobox->addItem(tr("Extern"), Employee::Extern);

    ui->activeCombobox->clear();
    ui->activeCombobox->addItem(tr("Yes"), Employee::Yes);
    ui->activeCombobox->addItem(tr("No"), Employee::No);
}

void EmployeeDialog::setOpenType (EmployeeDialog::DialogType type)
{
    qDebug() << "EmployeeDialog::setOpenType()";

    m_openType = type;
    setupEmployeeField();
}

void EmployeeDialog::setSelectedEmployee (Employee * employee)
{
    qDebug() << "EmployeeDialog::setSelectedEmployee()";

    Q_ASSERT(m_openType != EmployeeDialog::Add);

    m_employee = employee;
    fillEmployeeField();
}

void EmployeeDialog::setupEmployeeField ()
{
    qDebug() << "EmployeeDialog::setupEmployeeField()";

    switch (m_openType)
    {
    case Add:
        qDebug() << "EmployeeDialog::setupEmployeeField() - Add";
        ui->idText->setText("0");

        ui->nameText->setText("");
        ui->nameText->setReadOnly(false);

        ui->surnameText->setText("");
        ui->surnameText->setReadOnly(false);

        ui->usernameText->setText("");
        ui->usernameText->setReadOnly(false);

        ui->passwordText->setText("");
        ui->passwordText->setReadOnly(false);

        ui->sysroleCombobox->setEnabled(true);
        ui->roleCombobox->setEnabled(true);
        ui->companyCombobox->setEnabled(true);
        ui->activeCombobox->setEnabled(true);

        ui->sysroleCombobox->setCurrentIndex(0);
        ui->roleCombobox->setCurrentIndex(0);
        ui->companyCombobox->setCurrentIndex(0);
        ui->activeCombobox->setCurrentIndex(0);

        ui->noteText->setReadOnly(false);
        ui->noteText->setText("");
        break;
    case Edit:
        qDebug() << "EmployeeDialog::setupEmployeeField() - Edit";
        if (m_loggedUserSystemRole == Employee::Administrator)
        {
            ui->nameText->setReadOnly(false);
            ui->surnameText->setReadOnly(false);
            ui->usernameText->setReadOnly(false);
        }
        else
        {
            ui->nameText->setReadOnly(true);
            ui->surnameText->setReadOnly(true);
            ui->usernameText->setReadOnly(true);
        }

        /* The password can be changed in other field! */
        ui->passwordText->setReadOnly(true);

        ui->sysroleCombobox->setEnabled(true);
        ui->roleCombobox->setEnabled(true);
        ui->companyCombobox->setEnabled(true);
        ui->activeCombobox->setEnabled(true);

        ui->noteText->setReadOnly(false);
        break;
    case View:
        qDebug() << "EmployeeDialog::setupEmployeeField() - View";
        ui->nameText->setReadOnly(true);

        ui->surnameText->setReadOnly(true);

        ui->usernameText->setReadOnly(true);

        ui->passwordText->setReadOnly(true);

        ui->sysroleCombobox->setEnabled(false);
        ui->roleCombobox->setEnabled(false);
        ui->companyCombobox->setEnabled(false);
        ui->activeCombobox->setEnabled(false);

        ui->noteText->setReadOnly(true);
        break;
    default:
        Q_ASSERT(0);
        break;
    }
}

void EmployeeDialog::fillEmployeeField ()
{
    qDebug() << "EmployeeDialog::fillEmployeeField()";

    ui->idText->setText(QString::number(m_employee->getId()));

    ui->nameText->setText(m_employee->getName());
    ui->surnameText->setText(m_employee->getSurname());

    ui->usernameText->setText(m_employee->getUsername());
    ui->passwordText->setText(m_employee->getPassword());

    ui->roleCombobox->setCurrentIndex(m_employee->getRole());
    ui->sysroleCombobox->setCurrentIndex(m_employee->getSystemRole());
    ui->companyCombobox->setCurrentIndex(m_employee->getCompany());
    ui->activeCombobox->setCurrentIndex(m_employee->getActiveStatus());

    ui->noteText->setText(m_employee->getNote());
}

void EmployeeDialog::saveValues ()
{
    qDebug() << "EmployeeDialog::saveValues()";
    m_employee = 0;

    QRegExp name = QRegExp(QString::fromUtf8("^[a-zA-Zèéìòàù' ]+$"));
    QRegExp nick = QRegExp(QString::fromUtf8("[a-zA-Z0-9]{5,20}"));

    if (name.exactMatch(ui->nameText->text()))
    {
        qDebug() << "Name correct:" << ui->nameText->text();
    }
    else
    {
        qDebug() << "Name not correct:" << ui->nameText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Name not correct!"));
        return;
    }

    if (name.exactMatch(ui->surnameText->text()))
    {
        qDebug() << "Surname correct:" << ui->surnameText->text();
    }
    else
    {
        qDebug() << "Surname not correct:" << ui->surnameText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Surname not correct!"));
        return;
    }

    if (nick.exactMatch(ui->usernameText->text()))
    {
        qDebug() << "Username correct:" << ui->usernameText->text();
    }
    else
    {
        qDebug() << "Username not correct:" << ui->usernameText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Username not correct!"));
        return;
    }

    /* The password can be setted only during user creation and by a specific button in a home! */
    if (m_openType == Add)
    {
        if (nick.exactMatch(ui->passwordText->text()))
        {
            qDebug() << "Password correct:" << ui->passwordText->text();
        }
        else
        {
            qDebug() << "Password not correct:" << ui->usernameText->text();
            QMessageBox::critical(this, tr("Error"),
                tr("Password not correct!"));
            return;
        }
    }

    m_employee = new Employee(ui->surnameText->text(),ui->nameText->text());
    if (m_openType != Add) m_employee->setId(ui->idText->text().toUInt());
    m_employee->setUsername(ui->usernameText->text());
    if (m_openType == Add) m_employee->setPassword(ui->passwordText->text());
    m_employee->setRole(static_cast<Employee::Role>(
                            ui->roleCombobox->currentData().toInt())
                        );
    qDebug() << "Role:" << static_cast<Employee::Role>(
                    ui->roleCombobox->currentData().toInt());
    m_employee->setSystemRole(static_cast<Employee::SystemRole>(
                                  ui->sysroleCombobox->currentData().toInt())
                              );
    qDebug() << "System Role:" << static_cast<Employee::SystemRole>(
                    ui->sysroleCombobox->currentData().toInt());
    m_employee->setCompany(static_cast<Employee::Company>(
                               ui->companyCombobox->currentData().toInt())
                           );
    qDebug() << "Company:" << static_cast<Employee::Company>(
                    ui->companyCombobox->currentData().toInt());
    m_employee->setActiveStatus(static_cast<Employee::Active>(
                               ui->activeCombobox->currentData().toInt())
                           );
    qDebug() << "Active Status:" << static_cast<Employee::Active>(
                    ui->activeCombobox->currentData().toInt());
    m_employee->setNote(ui->noteText->toPlainText());
    qDebug() << "Note:" << ui->noteText->toPlainText();
}

void EmployeeDialog::apply()
{
    if (m_openType != EmployeeDialog::View)
        saveValues ();

    if (m_employee != 0)
        close();
}

void EmployeeDialog::noApply()
{
    if (m_openType != EmployeeDialog::View)
        m_employee = 0;

    close();
}

Employee* EmployeeDialog::getSavedEmployee ()
{
    if (m_employee)
        return m_employee;
    else
        return 0;
}
void EmployeeDialog::setLoggedUserRole(Employee::SystemRole systemRole,
                                       Employee::Role role)
{
    m_loggedUserRole = role;
    m_loggedUserSystemRole = systemRole;
}
