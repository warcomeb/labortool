/******************************************************************************
 * LabOrTool - Laboratory Organization Tool
 * Copyright (C) 2015 Marco Giammarini
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

#include "productiondialog.h"
#include "ui_productiondialog.h"

#include "metadata.h"

#include <QDebug>
#include <QMessageBox>

#include <QVariant>

ProductionDialog::ProductionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductionDialog),
    m_openType(ProductionDialog::Add),
    m_noteSelected(0),
    m_loggedUserRole(Employee::Student), /* Low level permissions */
    m_loggedUserSystemRole(Employee::User)
{
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION) + " - Production Dialog");

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(apply()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(noApply()));

//    fillCombobox();

//    setupActivityField();

//    /* Startup note table! */
//    m_noteModel = new QStandardItemModel(1, 4);
//    ui->noteTable->setModel(m_noteModel);
//    ui->noteTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    clearNotesTab();
//    updateNotesList();

//    connect(ui->noteTable->selectionModel(),
//            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
//            this,
//            SLOT(selectionChangedNotesTable(const QItemSelection &, const QItemSelection &)));

//    connect(ui->activityNoteDeleteButton,SIGNAL(clicked()),
//            this,SLOT(deleteNote()));
//    connect(ui->activityNoteEditButton,SIGNAL(clicked()),
//            this,SLOT(editNote()));
//    connect(ui->activityNoteAddButton,SIGNAL(clicked()),
//            this,SLOT(addNote()));
}

ProductionDialog::~ProductionDialog()
{
    delete ui;
}

void ProductionDialog::fillCombobox ()
{
    ui->statusCombobox->clear();
    ui->statusCombobox->addItem(tr("Not Started"), Production::NotStarted);
    ui->statusCombobox->addItem(tr("In Progress"), Production::InProgress);
    ui->statusCombobox->addItem(tr("Ended"), Production::Ended);
    ui->statusCombobox->addItem(tr("Postponed"), Production::Postponed);
    ui->statusCombobox->addItem(tr("Waiting"), Production::Waiting);
}

void ProductionDialog::setOpenType (ProductionDialog::DialogType type)
{
    qDebug() << "ProductionDialog::setOpenType()";

    ui->tabWidget->setCurrentIndex(0);

    m_openType = type;
    setupProductionField();
}

void ProductionDialog::setLoggedUserRole(Employee::SystemRole systemRole,
                                         Employee::Role role)
{
    m_loggedUserRole = role;
    m_loggedUserSystemRole = systemRole;
}

void ProductionDialog::saveValues ()
{
//    qDebug() << "ActivityDialog::saveValues()";
//    m_activity = 0;

//    QRegExp workCode = QRegExp(QString::fromUtf8("^[A-Z0-9-]{12}$"));


//    if (ui->titleText->text().isEmpty())
//    {
//        qDebug() << "ActivityDialog::saveValues() - Title is empty";
//        QMessageBox::critical(this, tr("Error"),
//            tr("Activity title is empty!"));
//        return;
//    }

//    if (workCode.exactMatch(ui->jobcodeText->text()))
//    {
//        qDebug() << "ActivityDialog::saveValues() - Job Code correct:" << ui->jobcodeText->text();
//    }
//    else
//    {
//        qDebug() << "ActivityDialog::saveValues() - Job Code not correct:" << ui->jobcodeText->text();
//        QMessageBox::critical(this, tr("Error"),
//            tr("Job Code not correct!"));
//        return;
//    }

//    m_activity = new Activity(ui->titleText->text());
//    if (m_openType != Add) m_activity->setId(ui->idText->text().toUInt());
//    m_activity->setDeadline(ui->deadlineEdit->date());
//    m_activity->setDescription(ui->descriptionText->toPlainText());
//    m_activity->setEmployee(qvariant_cast<uint>(ui->employeeCombobox->itemData(ui->employeeCombobox->currentIndex())));
//    m_activity->setWorkCode(ui->jobcodeText->text());

//    m_activity->setPriority(
//        static_cast<Activity::Priority>(
//            ui->priorityCombobox->currentData().toInt()
//        )
//    );
//    qDebug() << "ActivityDialog::saveValues() - Priority:" << static_cast<Activity::Priority>(
//        ui->priorityCombobox->currentData().toInt());

//    m_activity->setType(
//        static_cast<Activity::Type>(
//            ui->typeCombobox->currentData().toInt()
//        )
//    );
//    qDebug() << "ActivityDialog::saveValues() - Type:" << static_cast<Activity::Type>(
//        ui->typeCombobox->currentData().toInt());

//    m_activity->setStatus(
//        static_cast<Activity::Status>(
//            ui->statusCombobox->currentData().toInt()
//        )
//    );
//    qDebug() << "ActivityDialog::saveValues() - Status:" << static_cast<Activity::Status>(
//        ui->statusCombobox->currentData().toInt());
}

void ProductionDialog::prepareNewProduction (QVector<Employee*> employeesList)
{
    qDebug() << "ProductionDialog::prepareNewProduction()";

    m_employeesList = employeesList;
    m_notesList.clear();

    Q_ASSERT(m_openType == ProductionDialog::Add);

    updateEmployeesList();
    updateNotesList();

    clearNotesTab();

    qDebug() << "ProductionDialog::prepareNewProduction() - Exit!";
}

void ProductionDialog::setupProductionField ()
{
    switch (m_openType)
    {
    case Add:
        ui->idText->setText("0");

        ui->titleText->setText("");
        ui->titleText->setReadOnly(false);

        ui->jobcodeText->setText("");
        ui->jobcodeText->setReadOnly(false);

        ui->outputText->setText("");
        ui->outputText->setReadOnly(false);

        ui->statusCombobox->setEnabled(true);

        ui->employeeCombobox->setEnabled(true);

        ui->descriptionText->setReadOnly(false);
        ui->descriptionText->setPlainText("");

        /* Notes tab */
        ui->productionNoteDeleteButton->setEnabled(false);
        ui->productionNoteEditButton->setEnabled(false);
        ui->productionNoteAddButton->setEnabled(false);

        ui->saveButton->show();
        ui->saveButton->setText(tr("Save"));
        ui->cancelButton->show();
        ui->cancelButton->setText(tr("Cancel"));
        break;
    case Edit:
        ui->titleText->setReadOnly(false);

        ui->jobcodeText->setReadOnly(false);

        ui->outputText->setReadOnly(false);

        ui->statusCombobox->setEnabled(true);

        ui->employeeCombobox->setEnabled(true);

        ui->descriptionText->setReadOnly(false);

        /* Notes tab */
        if ((m_loggedUserSystemRole == Employee::Administrator) ||
            (m_loggedUserRole == Employee::Coordinator))
        {
            ui->productionNoteDeleteButton->setEnabled(true);
            ui->productionNoteEditButton->setEnabled(true);
            ui->productionNoteAddButton->setEnabled(true);
        }
        else if (m_loggedUserSystemRole == Employee::Editor)
        {
            ui->productionNoteDeleteButton->setEnabled(false);
            ui->productionNoteEditButton->setEnabled(true);
            ui->productionNoteAddButton->setEnabled(true);
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

        ui->outputText->setReadOnly(true);

        ui->statusCombobox->setEnabled(false);

        ui->employeeCombobox->setEnabled(false);

        ui->descriptionText->setReadOnly(true);

        /* Notes tab */
        ui->productionNoteDeleteButton->setEnabled(false);
        ui->productionNoteEditButton->setEnabled(false);
        ui->productionNoteAddButton->setEnabled(false);

        ui->saveButton->hide();
        ui->cancelButton->show();
        ui->cancelButton->setText(tr("Close"));
        break;
    default:
        Q_ASSERT(0);
        break;
    }
}

void ProductionDialog::updateEmployeesList ()
{
    qDebug() << "ProductionDialog::updateEmployeesList()";

    ui->employeeCombobox->clear();
    for (int row = 0; row < m_employeesList.size(); ++row)
    {
        QString name = (m_employeesList.at(row))->getSurname() + " " + (m_employeesList.at(row))->getName();
        uint id = (m_employeesList.at(row))->getId();
        qDebug() << "ProductionDialog::updateEmployeesList() - employee:" << name  << "Id" << id;
        ui->employeeCombobox->addItem(name,id);
    }
}

void ProductionDialog::updateNotesList (QVector<ProductionNote*> notesList)
{
    Q_ASSERT(isVisible());

    m_notesList = notesList;
    updateNotesList();

    if (m_notesList.size() > 0)
    {
        m_noteSelected = (m_notesList.at(0))->getId();
        updateNotesTab();
    }
    else
    {
        clearNotesTab();
    }
}

void ProductionDialog::updateNotesList ()
{
    qDebug() << "ProductionDialog::updateNotesList()";

    qDebug() << "ProductionDialog::updateNotesList() - setting table";
    m_noteModel->clear();
    m_noteModel->setColumnCount(4);

    m_noteModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_noteModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    m_noteModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Author"));
    m_noteModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Text"));

    qDebug() << "ProductionDialog::updateNotesList() - Notes size:" << m_notesList.size();

//    if (m_notesList.size()>0)
//    {
//        for (int row = 0; row < m_notesList.size(); ++row)
//        {
//            QStandardItem *item;

//            item = new QStandardItem(m_notesList.at(row).at(0));
//            m_noteModel->setItem(row, 0, item);

//            qDebug() << "ActivityDialog::updateNotesList() - Note creation:" << m_notesList.at(row).at(5);
//            qDebug() << "ActivityDialog::updateNotesList() - Note creation conversion:" <<
//                QDateTime::fromString(m_notesList.at(row).at(5),"yyyy-MM-ddThh:mm:ss");
//            item = new QStandardItem(
//                QDateTime::fromString(m_notesList.at(row).at(5),"yyyy-MM-ddThh:mm:ss").toString("dd.MM.yyyy hh:mm:ss"));
//            m_noteModel->setItem(row, 1, item);

//            uint author = m_notesList.at(row).at(3).toUInt();
//            for (int i = 0; i < m_employeesList.size(); ++i)
//            {
//                if (author == m_employeesList.at(i).at(0).toUInt())
//                {
//                    item = new QStandardItem(m_employeesList.at(i).at(1) + " " + m_employeesList.at(i).at(2));
//                    break;
//                }
//            }
//            m_noteModel->setItem(row, 2, item);

//            item = new QStandardItem(m_notesList.at(row).at(2));
//            m_noteModel->setItem(row, 3, item);
//        }
//    }
}

void ProductionDialog::keyPressEvent(QKeyEvent* e)
{
    if(e->key() != Qt::Key_Escape) noApply();
}

void ProductionDialog::apply()
{
    if (m_openType != ProductionDialog::View)
        saveValues ();

    if (m_production != 0)
    {
        m_noteSelected = 0;
        close();
    }
}

void ProductionDialog::noApply()
{
    if (m_openType != ProductionDialog::View)
        m_production = 0;

    m_noteSelected = 0;

    close();
}

Production* ProductionDialog::getSavedProduction ()
{
    if (m_production)
        return m_production;
    else
        return 0;
}

void ProductionDialog::selectionChangedNotesTable(const QItemSelection & sel,
                                                const QItemSelection & des)
{
    qDebug() << "ProductionDialog::selectionChangedNotesTable()";

//    QModelIndexList indexes = sel.indexes();
//    qDebug() << "ProductionDialog::selectionChangedNotesTable() - selected number" << indexes.count();

//    qDebug() << "ProductionDialog::selectionChangedNotesTable() - row selected" << indexes.at(0).row();
//    m_noteSelected = m_noteModel->item(indexes.at(0).row(),0)->text().toUInt();
//    qDebug() << "ProductionDialog::selectionChangedNotesTable() - note selected" << m_noteSelected;

//    updateNotesTab();

//    qDebug() << "ProductionDialog::selectionChangedNotesTable() - Exit!";
}

void ProductionDialog::updateNotesTab()
{
    qDebug() << "ProductionDialog::updateNotesTab()!";

//    bool noteFounded = false;

//    for (int i = 0; i < m_notesList.size(); ++i)
//    {
//        if (m_noteSelected == m_notesList.at(i).at(0).toUInt())
//        {
//            noteFounded = true;
//            qDebug() << "ActivityDialog::selectionChangedNotesTable() - Note founded!";

//            ui->textNoteEdit->setPlainText(m_notesList.at(i).at(2));

//            uint creationAuthor = m_notesList.at(i).at(3).toUInt();
//            for (int j = 0; j < m_employeesList.size(); ++j)
//            {
//                if (creationAuthor == m_employeesList.at(j).at(0).toUInt())
//                {
//                    ui->authorNoteCreEdit->setText(m_employeesList.at(j).at(1) + " " + m_employeesList.at(j).at(2));
//                    qDebug() << "ActivityDialog::selectionChangedNotesTable() - Note creation author" <<
//                                m_employeesList.at(j).at(1) + " " + m_employeesList.at(j).at(2);
//                    break;
//                }
//            }

//            uint modificatioAuthor = m_notesList.at(i).at(4).toUInt();
//            for (int j = 0; j < m_employeesList.size(); ++j)
//            {
//                if (modificatioAuthor == m_employeesList.at(j).at(0).toUInt())
//                {
//                    ui->authorNoteModEdit->setText(m_employeesList.at(j).at(1) + " " + m_employeesList.at(j).at(2));
//                    qDebug() << "ActivityDialog::selectionChangedNotesTable() - Note modification author" <<
//                                m_employeesList.at(j).at(1) + " " + m_employeesList.at(j).at(2);
//                    break;
//                }
//            }

//            ui->dateNoteCreEdit->setDateTime(QDateTime::fromString(m_notesList.at(i).at(5),"yyyy-MM-ddThh:mm:ss"));
//            ui->dateNoteModEdit->setDateTime(QDateTime::fromString(m_notesList.at(i).at(6),"yyyy-MM-ddThh:mm:ss"));
//            break;
//        }
//    }

//    if (!noteFounded)
//        clearNotesTab();

    qDebug() << "ProductionDialog::updateNotesTab() - Exit!";
}

void ProductionDialog::clearNotesTab()
{
    qDebug() << "ProductionDialog::clearNotesTab()";

    ui->textNoteEdit->setPlainText("");

    ui->authorNoteCreEdit->setText("");
    ui->authorNoteModEdit->setText("");

    ui->dateNoteCreEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateNoteModEdit->setDateTime(QDateTime::currentDateTime());

    qDebug() << "ProductionDialog::clearNotesTab() - Exit!";
}

void ProductionDialog::addNote()
{
    qDebug() << "ProductionDialog::addNote()";
    qDebug() << "ProductionDialog::addNote() - Production Id" << m_production->getId();
    emit addNoteButton(m_production->getId());
    qDebug() << "ProductionDialog::addNote() - Exit!";
}

void ProductionDialog::editNote()
{
    qDebug() << "ProductionDialog::editNote()";
    emit editNoteButton(m_noteSelected);
    qDebug() << "ProductionDialog::editNote() - Exit!";
}

void ProductionDialog::deleteNote()
{
    qDebug() << "ProductionDialog::deleteNote()";
    emit deleteNoteButton(m_noteSelected);
    qDebug() << "ProductionDialog::deleteNote() - Exit!";
}
