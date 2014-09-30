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

#include "activitydialog.h"
#include "ui_activitydialog.h"

#include "metadata.h"

#include <QDebug>
#include <QMessageBox>

ActivityDialog::ActivityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivityDialog),
    m_openType(ActivityDialog::DialogType_Add)
{
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION) + " - Activity Dialog");

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(noApply()));

    fillCombobox();

    setupActivityField();
}

ActivityDialog::~ActivityDialog()
{
    if (m_activity)
        delete m_activity;

    delete ui;
}

void ActivityDialog::fillCombobox ()
{
    ui->statusCombobox->clear();
    ui->statusCombobox->addItem(tr("Not Started"), Activity::NotStarted);
    ui->statusCombobox->addItem(tr("In Progress"), Activity::InProgress);
    ui->statusCombobox->addItem(tr("Ended"), Activity::Ended);
    ui->statusCombobox->addItem(tr("Postponed"), Activity::Postponed);
    ui->statusCombobox->addItem(tr("Waiting"), Activity::Waiting);

    ui->typeCombobox->clear();
    ui->typeCombobox->addItem(tr("Board"), Activity::Board);
    ui->typeCombobox->addItem(tr("Repair"), Activity::Repair);
    ui->typeCombobox->addItem(tr("Support"), Activity::Support);
    ui->typeCombobox->addItem(tr("Firmware"), Activity::Firmware);
    ui->typeCombobox->addItem(tr("Production"), Activity::Production);

    ui->priorityCombobox->clear();
    ui->priorityCombobox->addItem(tr("Low"), Activity::Low);
    ui->priorityCombobox->addItem(tr("Medium"), Activity::Medium);
    ui->priorityCombobox->addItem(tr("High"), Activity::High);
    ui->priorityCombobox->addItem(tr("Now"), Activity::Now);
}

void ActivityDialog::setOpenType (ActivityDialog::DialogType type)
{
    qDebug() << "ActivityDialog::setOpenType()";

    m_openType = type;
    setupActivityField();
}

void ActivityDialog::setSelectedActivity (Activity * activity)
{
    qDebug() << "ActivityDialog::setSelectedActivity()";
    m_activity = activity;
    if (m_openType != ActivityDialog::DialogType_Add)
        fillActivityFields();
}

void ActivityDialog::setupActivityField ()
{
    switch (m_openType)
    {
    case DialogType_Add:
        ui->idText->setText("0");

        ui->titleText->setText("");
        ui->titleText->setEnabled(true);

        ui->jobcodeText->setText("");
        ui->jobcodeText->setEnabled(true);

        ui->typeCombobox->setEnabled(true);
        ui->statusCombobox->setEnabled(true);
        ui->priorityCombobox->setEnabled(true);

        ui->employeeCombobox->setEnabled(true);

        ui->deadlineEdit->setEnabled(true);
        ui->deadlineEdit->setDateTime(QDateTime::currentDateTime());

        ui->descriptionText->setEnabled(true);
        ui->descriptionText->setText("");
        break;
    case DialogType_Edit:
        ui->titleText->setEnabled(true);

        ui->jobcodeText->setEnabled(true);

        ui->typeCombobox->setEnabled(true);
        ui->statusCombobox->setEnabled(true);
        ui->priorityCombobox->setEnabled(true);

        ui->employeeCombobox->setEnabled(true);

        ui->deadlineEdit->setEnabled(true);

        ui->descriptionText->setEnabled(true);
        break;
    case DialogType_View:
        ui->titleText->setEnabled(false);

        ui->jobcodeText->setEnabled(false);

        ui->typeCombobox->setEnabled(false);
        ui->statusCombobox->setEnabled(false);
        ui->priorityCombobox->setEnabled(false);

        ui->employeeCombobox->setEnabled(false);

        ui->deadlineEdit->setEnabled(false);

        ui->descriptionText->setEnabled(false);
        break;
    default:
        /* mmm */
        break;
    }
}

void ActivityDialog::updateEmployeesList (QVector<QVector<QString> > employeesList)
{
    qDebug() << "ActivityDialog::updateEmployeesList()";

    ui->employeeCombobox->clear();
    for (int row = 0; row < employeesList.size(); ++row)
    {
        QString name = employeesList.at(row).at(1) + " " + employeesList.at(row).at(2);
        qDebug() << "ActivityDialog::updateEmployeesList() - employee:" << name;
        ui->employeeCombobox->addItem(name,employeesList.at(row).at(0).toUInt());
    }
}

void ActivityDialog::fillActivityFields ()
{
    qDebug() << "ActivityDialog::fillActivityField()";

    ui->idText->setText(QString::number(m_activity->getId()));

    /* ToDo */

}

void ActivityDialog::saveValues ()
{
    qDebug() << "ActivityDialog::saveValues()";
    m_activity = 0;

    QRegExp workCode = QRegExp(QString::fromUtf8("^[A-Z0-9-]{12}$"));

    if (ui->titleText->text().isEmpty())
    {
        qDebug() << "Title is empty";
        QMessageBox::critical(this, tr("Error"),
            tr("Activity title is empty!"));
    }

    if (workCode.exactMatch(ui->jobcodeText->text()))
    {
        qDebug() << "Job Code correct:" << ui->jobcodeText->text();
    }
    else
    {
        qDebug() << "Job Code not correct:" << ui->jobcodeText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Job Code not correct!"));
//        return;
    }

    m_activity = new Activity(ui->jobcodeText->text());
    if (m_openType != DialogType_Add) m_activity->setId(ui->idText->text().toUInt());
    m_activity->setDeadline(ui->deadlineEdit->date());
    m_activity->setDescription(ui->descriptionText->toPlainText());
    m_activity->setEmployee(ui->employeeCombobox->currentIndex());
    m_activity->setWorkCode(ui->jobcodeText->text());

    m_activity->setPriority(
        static_cast<Activity::Priority>(
            ui->priorityCombobox->currentData().toInt()
        )
    );
    qDebug() << "Priority:" << static_cast<Activity::Priority>(
        ui->priorityCombobox->currentData().toInt());

    m_activity->setType(
        static_cast<Activity::Type>(
            ui->typeCombobox->currentData().toInt()
        )
    );
    qDebug() << "Type:" << static_cast<Activity::Type>(
        ui->typeCombobox->currentData().toInt());

    m_activity->setStatus(
        static_cast<Activity::Status>(
            ui->statusCombobox->currentData().toInt()
        )
    );
    qDebug() << "Status:" << static_cast<Activity::Status>(
        ui->statusCombobox->currentData().toInt());

}

void ActivityDialog::apply()
{
    if (m_openType != ActivityDialog::DialogType_View)
        saveValues ();

    close();
}

void ActivityDialog::noApply()
{
    if (m_openType != ActivityDialog::DialogType_View)
        m_activity = 0;
    close();
}

Activity* ActivityDialog::getSavedActivity ()
{
    if (m_activity)
        return m_activity;
    else
        return 0;
}
