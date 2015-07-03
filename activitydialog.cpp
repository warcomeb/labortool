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

#include <QVariant>

ActivityDialog::ActivityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivityDialog),
    m_openType(ActivityDialog::Add),
    m_noteSelected(0),
    m_loggedUserRole(Employee::Student), /* Low level permissions */
    m_loggedUserSystemRole(Employee::User)
{
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION) + " - Activity Dialog");

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(noApply()));

    fillCombobox();

    setupActivityField();

    /* Startup note table! */
    m_noteModel = new QStandardItemModel(1, 4);
    ui->noteTable->setModel(m_noteModel);
    ui->noteTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    clearNotesTab();
    updateNotesList();

    connect(ui->noteTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(selectionChangedNotesTable(const QItemSelection &, const QItemSelection &)));

    connect(ui->activityNoteDeleteButton,SIGNAL(clicked()),
            this,SLOT(deleteNote()));
    connect(ui->activityNoteEditButton,SIGNAL(clicked()),
            this,SLOT(editNote()));
    connect(ui->activityNoteAddButton,SIGNAL(clicked()),
            this,SLOT(addNote()));
}

ActivityDialog::~ActivityDialog()
{
    if (m_activity)
        delete m_activity;

    delete ui;
}

void ActivityDialog::setLoggedUserRole(Employee::SystemRole systemRole,
                                       Employee::Role role)
{
    m_loggedUserRole = role;
    m_loggedUserSystemRole = systemRole;
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

    ui->tabWidget->setCurrentIndex(0);

    m_openType = type;
    setupActivityField();
}

void ActivityDialog::setSelectedActivity (Activity * activity,
                                          QVector<Employee*> employeesList,
                                          QVector<Note *> notesList)
{
    qDebug() << "ActivityDialog::setSelectedActivity()";

    m_activity = activity;
    m_employeesList = employeesList;
    m_notesList = notesList;

    Q_ASSERT(m_openType != ActivityDialog::Add);

    updateEmployeesList();
    clearNotesTab();
    updateNotesList();
    fillActivityFields();

    qDebug() << "ActivityDialog::setSelectedActivity() - Exit!";
}

void ActivityDialog::prepareNewActivity (QVector<Employee*> employeesList)
{
    qDebug() << "ActivityDialog::prepareNewActivity()";

    m_employeesList = employeesList;
    m_notesList.clear();

    Q_ASSERT(m_openType == ActivityDialog::Add);

    updateEmployeesList();
    updateNotesList();

    clearNotesTab();

    qDebug() << "ActivityDialog::prepareNewActivity() - Exit!";
}

void ActivityDialog::setupActivityField ()
{
    switch (m_openType)
    {
    case Add:
        ui->idText->setText("0");

        ui->titleText->setText("");
        ui->titleText->setReadOnly(false);

        ui->jobcodeText->setText("");
        ui->jobcodeText->setReadOnly(false);

        ui->typeCombobox->setEnabled(true);
        ui->statusCombobox->setEnabled(true);
        ui->priorityCombobox->setEnabled(true);

        ui->employeeCombobox->setEnabled(true);

        ui->deadlineEdit->setReadOnly(false);
        ui->deadlineEdit->setDateTime(QDateTime::currentDateTime());

        ui->descriptionText->setReadOnly(false);
        ui->descriptionText->setPlainText("");

        /* Notes tab */
        ui->activityNoteDeleteButton->setEnabled(false);
        ui->activityNoteEditButton->setEnabled(false);
        ui->activityNoteAddButton->setEnabled(false);

        ui->saveButton->show();
        ui->saveButton->setText(tr("Save"));
        ui->cancelButton->show();
        ui->cancelButton->setText(tr("Cancel"));
        break;
    case Edit:
        ui->titleText->setReadOnly(false);

        ui->jobcodeText->setReadOnly(false);

        ui->typeCombobox->setEnabled(true);
        ui->statusCombobox->setEnabled(true);
        ui->priorityCombobox->setEnabled(true);

        ui->employeeCombobox->setEnabled(true);

        ui->deadlineEdit->setReadOnly(false);

        ui->descriptionText->setReadOnly(false);

        /* Notes tab */
        if ((m_loggedUserSystemRole == Employee::Administrator) ||
            (m_loggedUserRole == Employee::Coordinator))
        {
            ui->activityNoteDeleteButton->setEnabled(true);
            ui->activityNoteEditButton->setEnabled(true);
            ui->activityNoteAddButton->setEnabled(true);
        }
        else if (m_loggedUserSystemRole == Employee::Editor)
        {
            ui->activityNoteDeleteButton->setEnabled(false);
            ui->activityNoteEditButton->setEnabled(true);
            ui->activityNoteAddButton->setEnabled(true);
        }
        else
        {
            Q_ASSERT(0);
        }

        ui->saveButton->show();
        ui->saveButton->setText(tr("Save"));
        ui->cancelButton->show();
        ui->cancelButton->setText(tr("Cancel"));
        break;
    case View:
        ui->titleText->setReadOnly(true);

        ui->jobcodeText->setReadOnly(true);

        ui->typeCombobox->setEnabled(false);
        ui->statusCombobox->setEnabled(false);
        ui->priorityCombobox->setEnabled(false);

        ui->employeeCombobox->setEnabled(false);

        ui->deadlineEdit->setReadOnly(true);

        ui->descriptionText->setReadOnly(true);

        /* Notes tab */
        ui->activityNoteDeleteButton->setEnabled(false);
        ui->activityNoteEditButton->setEnabled(false);
        ui->activityNoteAddButton->setEnabled(false);

        ui->saveButton->hide();
        ui->cancelButton->show();
        ui->cancelButton->setText(tr("Close"));
        break;
    default:
        Q_ASSERT(0);
        break;
    }
}

void ActivityDialog::updateEmployeesList ()
{
    qDebug() << "ActivityDialog::updateEmployeesList()";

    ui->employeeCombobox->clear();
    for (int row = 0; row < m_employeesList.size(); ++row)
    {
        QString name = (m_employeesList.at(row))->getSurname() + " " + (m_employeesList.at(row))->getName();
        uint id = (m_employeesList.at(row))->getId();
        qDebug() << "ActivityDialog::updateEmployeesList() - employee:" << name  << "Id" << id;
        ui->employeeCombobox->addItem(name,id);
    }
}

void ActivityDialog::updateNotesList (QVector<Note *> notesList)
{
    Q_ASSERT(isVisible());

    m_notesList = notesList;
    updateNotesList();

    if (m_notesList.size() > 0)
    {
        m_noteSelected = m_notesList.at(0)->getId();
        updateNotesTab();
    }
    else
    {
        clearNotesTab();
    }
}

void ActivityDialog::updateNotesList ()
{
    qDebug() << "ActivityDialog::updateNotesList()";

    qDebug() << "ActivityDialog::updateNotesList() - setting table";
    m_noteModel->clear();
    m_noteModel->setColumnCount(4);

    m_noteModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_noteModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    m_noteModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Author"));
    m_noteModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Text"));

    qDebug() << "ActivityDialog::updateNotesList() - Notes size:" << m_notesList.size();
    qDebug() << "ActivityDialog::updateNotesList() - Notes " << m_notesList;

    if (m_notesList.size()>0)
    {
        for (int row = 0; row < m_notesList.size(); ++row)
        {
            QStandardItem *item;

            item = new QStandardItem(QString::number(m_notesList.at(row)->getId()));
            m_noteModel->setItem(row, 0, item);

            qDebug() << "ActivityDialog::updateNotesList() - Note creation:" << m_notesList.at(row)->getCreationDate();
            item = new QStandardItem(
                (m_notesList.at(row)->getCreationDate()).toString("yyyy-MM-dd hh:mm:ss"));
            m_noteModel->setItem(row, 1, item);

            uint author = m_notesList.at(row)->getCreationEmployee();
            for (int i = 0; i < m_employeesList.size(); ++i)
            {
                if (author == (m_employeesList.at(i))->getId())
                {
                    item = new QStandardItem(m_employeesList.at(i)->getSurname() + " " +
                                             m_employeesList.at(i)->getName());
                    break;
                }
            }
            m_noteModel->setItem(row, 2, item);

            item = new QStandardItem(m_notesList.at(row)->getText());
            m_noteModel->setItem(row, 3, item);
        }
    }
}

void ActivityDialog::fillActivityFields ()
{
    qDebug() << "ActivityDialog::fillActivityField()";

    ui->idText->setText(QString::number(m_activity->getId()));
    ui->titleText->setText(m_activity->getTitle());
    ui->descriptionText->setPlainText(m_activity->getDescription());
    ui->jobcodeText->setText(m_activity->getWorkCode());

    ui->deadlineEdit->setDate(m_activity->getDeadline());

    ui->statusCombobox->setCurrentIndex(m_activity->getStatus());
    ui->priorityCombobox->setCurrentIndex(m_activity->getPriority());
    ui->typeCombobox->setCurrentIndex(m_activity->getType());

    qDebug() << "ActivityDialog::fillActivityField() - count employee" << ui->employeeCombobox->count();
    for (int i  = 0; i <  ui->employeeCombobox->count(); ++i)
    {
        qDebug() << "ActivityDialog::fillActivityField() - employee combobox" <<
                    ui->employeeCombobox->itemData(i);
        uint employeeId = qvariant_cast<uint>(ui->employeeCombobox->itemData(i));
        qDebug() << "ActivityDialog::fillActivityField() - Test employee" << employeeId;
        if (employeeId == m_activity->getEmployee())
        {
            qDebug() << "ActivityDialog::fillActivityField() - employee" << employeeId;
            ui->employeeCombobox->setCurrentIndex(i);
            break;
        }
    }
}

void ActivityDialog::saveValues ()
{
    qDebug() << "ActivityDialog::saveValues()";
    m_activity = 0;

    QRegExp workCode = QRegExp(QString::fromUtf8("^[A-Z0-9-]{12}$"));


    if (ui->titleText->text().isEmpty())
    {
        qDebug() << "ActivityDialog::saveValues() - Title is empty";
        QMessageBox::critical(this, tr("Error"),
            tr("Activity title is empty!"));
        return;
    }

    if (workCode.exactMatch(ui->jobcodeText->text()))
    {
        qDebug() << "ActivityDialog::saveValues() - Job Code correct:" << ui->jobcodeText->text();
    }
    else
    {
        qDebug() << "ActivityDialog::saveValues() - Job Code not correct:" << ui->jobcodeText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Job Code not correct!"));
        return;
    }

    m_activity = new Activity(ui->titleText->text());
    if (m_openType != Add) m_activity->setId(ui->idText->text().toUInt());
    m_activity->setDeadline(ui->deadlineEdit->date());
    m_activity->setDescription(ui->descriptionText->toPlainText());
    m_activity->setEmployee(qvariant_cast<uint>(ui->employeeCombobox->itemData(ui->employeeCombobox->currentIndex())));
    m_activity->setWorkCode(ui->jobcodeText->text());

    m_activity->setPriority(
        static_cast<Activity::Priority>(
            ui->priorityCombobox->currentData().toInt()
        )
    );
    qDebug() << "ActivityDialog::saveValues() - Priority:" << static_cast<Activity::Priority>(
        ui->priorityCombobox->currentData().toInt());

    m_activity->setType(
        static_cast<Activity::Type>(
            ui->typeCombobox->currentData().toInt()
        )
    );
    qDebug() << "ActivityDialog::saveValues() - Type:" << static_cast<Activity::Type>(
        ui->typeCombobox->currentData().toInt());

    m_activity->setStatus(
        static_cast<Activity::Status>(
            ui->statusCombobox->currentData().toInt()
        )
    );
    qDebug() << "ActivityDialog::saveValues() - Status:" << static_cast<Activity::Status>(
        ui->statusCombobox->currentData().toInt());
}

void ActivityDialog::apply()
{
    if (m_openType != ActivityDialog::View)
        saveValues ();

    if (m_activity != 0)
    {
        m_noteSelected = 0;
        close();
    }
}

void ActivityDialog::noApply()
{
    if (m_openType != ActivityDialog::View)
        m_activity = 0;

    m_noteSelected = 0;

    close();
}

Activity* ActivityDialog::getSavedActivity ()
{
    if (m_activity)
        return m_activity;
    else
        return 0;
}

void ActivityDialog::selectionChangedNotesTable(const QItemSelection & sel,
                                                const QItemSelection & des)
{
    qDebug() << "ActivityDialog::selectionChangedNotesTable()";

    QModelIndexList indexes = sel.indexes();
    qDebug() << "ActivityDialog::selectionChangedNotesTable() - selected number" << indexes.count();

    qDebug() << "ActivityDialog::selectionChangedNotesTable() - row selected" << indexes.at(0).row();
    m_noteSelected = m_noteModel->item(indexes.at(0).row(),0)->text().toUInt();
    qDebug() << "ActivityDialog::selectionChangedNotesTable() - note selected" << m_noteSelected;

    updateNotesTab();

    qDebug() << "ActivityDialog::selectionChangedNotesTable() - Exit!";
}

void ActivityDialog::updateNotesTab()
{
    qDebug() << "ActivityDialog::updateNotesTab()!";

    bool noteFounded = false;

    for (int i = 0; i < m_notesList.size(); ++i)
    {
        if (m_noteSelected == m_notesList.at(i)->getId())
        {
            noteFounded = true;
            qDebug() << "ActivityDialog::selectionChangedNotesTable() - Note founded!";

            ui->textNoteEdit->setPlainText(m_notesList.at(i)->getText());

            uint creationAuthor = m_notesList.at(i)->getCreationEmployee();
            for (int j = 0; j < m_employeesList.size(); ++j)
            {
                if (creationAuthor == m_employeesList.at(j)->getId())
                {
                    ui->authorNoteCreEdit->setText(m_employeesList.at(j)->getSurname() + " " +
                                                   m_employeesList.at(j)->getName());
                    qDebug() << "ActivityDialog::selectionChangedNotesTable() - Note creation author" <<
                                m_employeesList.at(j)->getSurname() + " " +
                                m_employeesList.at(j)->getName();
                    break;
                }
            }

            uint modificatioAuthor = m_notesList.at(i)->getModificationEmployee();
            for (int j = 0; j < m_employeesList.size(); ++j)
            {
                if (modificatioAuthor == m_employeesList.at(j)->getId())
                {
                    ui->authorNoteModEdit->setText(m_employeesList.at(j)->getSurname() + " " +
                                                   m_employeesList.at(j)->getName());
                    qDebug() << "ActivityDialog::selectionChangedNotesTable() - Note modification author" <<
                                m_employeesList.at(j)->getSurname() + " " +
                                m_employeesList.at(j)->getName();
                    break;
                }
            }

            ui->dateNoteCreEdit->setDateTime(m_notesList.at(i)->getCreationDate());
            ui->dateNoteModEdit->setDateTime(m_notesList.at(i)->getModificationDate());
            break;
        }
    }

    if (!noteFounded)
        clearNotesTab();


    qDebug() << "ActivityDialog::updateNotesTab() - Exit!";
}

void ActivityDialog::clearNotesTab()
{
    qDebug() << "ActivityDialog::clearNotesTab()";

    ui->textNoteEdit->setPlainText("");

    ui->authorNoteCreEdit->setText("");
    ui->authorNoteModEdit->setText("");

    ui->dateNoteCreEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateNoteModEdit->setDateTime(QDateTime::currentDateTime());

    qDebug() << "ActivityDialog::clearNotesTab() - Exit!";
}

void ActivityDialog::addNote()
{
    qDebug() << "ActivityDialog::addNote()";
    qDebug() << "ActivityDialog::addNote() - Activity Id" << m_activity->getId();
    emit addNoteButton(m_activity->getId());
    qDebug() << "ActivityDialog::addNote() - Exit!";
}

void ActivityDialog::editNote()
{
    qDebug() << "ActivityDialog::editNote()";
    emit editNoteButton(m_noteSelected);
    qDebug() << "ActivityDialog::editNote() - Exit!";
}

void ActivityDialog::deleteNote()
{
    qDebug() << "ActivityDialog::deleteNote()";
    emit deleteNoteButton(m_noteSelected);
    qDebug() << "ActivityDialog::deleteNote() - Exit!";
}

void ActivityDialog::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Escape) noApply();
}
