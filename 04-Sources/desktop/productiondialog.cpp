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

    fillCombobox();

    setupField();

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

    connect(ui->productionNoteDeleteButton,SIGNAL(clicked()),
            this,SLOT(deleteNote()));
    connect(ui->productionNoteEditButton,SIGNAL(clicked()),
            this,SLOT(editNote()));
    connect(ui->productionNoteAddButton,SIGNAL(clicked()),
            this,SLOT(addNote()));
}

ProductionDialog::~ProductionDialog()
{
//    if (m_production)
//        delete m_production;

    delete ui;
}

void ProductionDialog::translateUi()
{
    ui->retranslateUi(this);
}

void ProductionDialog::setLoggedUserRole(Employee::SystemRole systemRole,
                                         Employee::Role role)
{
    m_loggedUserRole = role;
    m_loggedUserSystemRole = systemRole;
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
    setupField();
}

void ProductionDialog::setSelectedProduction (Production * production,
                                              QVector<Employee*> employeesList,
                                              QVector<Note *> notesList)
{
    qDebug() << "ProductionDialog::setSelectedProduction()";

    m_production = production;
    m_employeesList = employeesList;
    m_notesList = notesList;

    Q_ASSERT(m_openType != ProductionDialog::Add);

    updateEmployeesList();
    clearNotesTab();
    updateNotesList();
    fillProductionFields();

    qDebug() << "ProductionDialog::setSelectedProduction() - Exit!";
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

void ProductionDialog::setupField ()
{
    switch (m_openType)
    {
    case Add:
        ui->idText->setText("0");

        ui->boardNameText->setText("");
        ui->boardNameText->setReadOnly(false);

        ui->quantityText->setValue(1);
        ui->quantityText->setReadOnly(false);

        ui->jobcodeText->setText("");
        ui->jobcodeText->setReadOnly(false);

        ui->outputText->setText("");
        ui->outputText->setReadOnly(false);

        ui->statusCombobox->setEnabled(true);

        ui->employeeCombobox->setEnabled(true);
        ui->supplierCombobox->setEnabled(true);

        ui->descriptionText->setReadOnly(false);
        ui->descriptionText->setPlainText("");

        ui->deadlineEdit->setReadOnly(false);
        ui->deadlineEdit->setDateTime(QDateTime::currentDateTime());

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
        ui->boardNameText->setReadOnly(false);

        ui->quantityText->setReadOnly(false);

        ui->jobcodeText->setReadOnly(false);

        ui->outputText->setReadOnly(false);

        ui->deadlineEdit->setReadOnly(false);

        ui->statusCombobox->setEnabled(true);

        ui->employeeCombobox->setEnabled(true);
        ui->supplierCombobox->setEnabled(true);

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
        ui->boardNameText->setReadOnly(true);

        ui->quantityText->setReadOnly(true);

        ui->jobcodeText->setReadOnly(true);

        ui->outputText->setReadOnly(true);

        ui->statusCombobox->setEnabled(false);

        ui->employeeCombobox->setEnabled(false);
        ui->supplierCombobox->setEnabled(false);

        ui->deadlineEdit->setReadOnly(true);

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

void ProductionDialog::updateNotesList (QVector<Note*> notesList)
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
    qDebug() << "ProductionDialog::updateNotesList() - Notes " << m_notesList;

    if (m_notesList.size()>0)
    {
        for (int row = 0; row < m_notesList.size(); ++row)
        {
            QStandardItem *item;

            item = new QStandardItem(QString::number(m_notesList.at(row)->getId()));
            m_noteModel->setItem(row, 0, item);

            qDebug() << "ProductionDialog::updateNotesList() - Note creation:" << m_notesList.at(row)->getCreationDate();
            item = new QStandardItem(
                m_notesList.at(row)->getCreationDate().toString("yyyy-MM-dd hh:mm:ss"));
            m_noteModel->setItem(row, 1, item);

            uint author = m_notesList.at(row)->getCreationEmployee();
            for (int i = 0; i < m_employeesList.size(); ++i)
            {
                if (author == m_employeesList.at(i)->getId())
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

void ProductionDialog::fillProductionFields ()
{
    qDebug() << "ProductionDialog::fillProductionFields()";

    ui->idText->setText(QString::number(m_production->getId()));
    ui->boardNameText->setText(m_production->getBoardName());
    ui->quantityText->setValue(m_production->getQuantity());
    ui->descriptionText->setPlainText(m_production->getDescription());
    ui->jobcodeText->setText(m_production->getWorkCode());
    ui->outputText->setText(m_production->getOutputCode());
    ui->deadlineEdit->setDate(m_production->getDeadline());

    ui->statusCombobox->setCurrentIndex(m_production->getStatus());
    qDebug() << "ProductionDialog::fillProductionFields() - status" << m_production->getStatus();

    qDebug() << "ProductionDialog::fillProductionFields() - count employee" << ui->employeeCombobox->count();
    for (int i  = 0; i <  ui->employeeCombobox->count(); ++i)
    {
        qDebug() << "ProductionDialog::fillProductionFields() - employee combobox" <<
                    ui->employeeCombobox->itemData(i);
        uint employeeId = qvariant_cast<uint>(ui->employeeCombobox->itemData(i));
        qDebug() << "ProductionDialog::fillProductionFields() - Test employee" << employeeId;
        if (employeeId == m_production->getEmployee())
        {
            qDebug() << "ProductionDialog::fillProductionFields() - employee" << employeeId;
            ui->employeeCombobox->setCurrentIndex(i);
            break;
        }
    }
}

void ProductionDialog::saveValues ()
{
    qDebug() << "ProductionDialog::saveValues()";

    QRegExp workCode = QRegExp(QString::fromUtf8("^[A-Z0-9-]{12}$"));

    if (ui->boardNameText->text().isEmpty())
    {
        qDebug() << "ProductionDialog::saveValues() - Board name is empty";
        QMessageBox::critical(this, tr("Error"),
            tr("Production board name is empty!"));
        return;
    }

    if (workCode.exactMatch(ui->jobcodeText->text()))
    {
        qDebug() << "ProductionDialog::saveValues() - Job Code correct:" << ui->jobcodeText->text();
    }
    else
    {
        qDebug() << "ProductionDialog::saveValues() - Job Code not correct:" << ui->jobcodeText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Work Code not correct!"));
        return;
    }

    if (!ui->outputText->text().isEmpty())
    {
        qDebug() << "ProductionDialog::saveValues() - Output Code correct:" << ui->outputText->text();
    }
    else
    {
        qDebug() << "ProductionDialog::saveValues() - Output Code not correct:" << ui->outputText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Output Code not correct!"));
        return;
    }

    if (m_openType == Add)
    {
        m_production = 0;
        m_production = new Production(ui->boardNameText->text());
    }
    else
    {
        m_production->setBoardName(ui->boardNameText->text());
    }

    if (m_openType != Add) m_production->setId(ui->idText->text().toUInt());

    m_production->setQuantity(ui->quantityText->value());
    m_production->setDescription(ui->descriptionText->toPlainText());
    m_production->setEmployee(qvariant_cast<uint>(ui->employeeCombobox->itemData(ui->employeeCombobox->currentIndex())));
    m_production->setWorkCode(ui->jobcodeText->text());
    m_production->setOutputCode(ui->outputText->text());
    m_production->setDeadline(ui->deadlineEdit->date());

    m_production->setStatus(
        static_cast<Production::Status>(
            ui->statusCombobox->currentData().toInt()
        )
    );

    /* TODO: Supplier!! */
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

    QModelIndexList indexes = sel.indexes();
    qDebug() << "ProductionDialog::selectionChangedNotesTable() - selected number" << indexes.count();

    qDebug() << "ProductionDialog::selectionChangedNotesTable() - row selected" << indexes.at(0).row();
    m_noteSelected = m_noteModel->item(indexes.at(0).row(),0)->text().toUInt();
    qDebug() << "ProductionDialog::selectionChangedNotesTable() - note selected" << m_noteSelected;

    updateNotesTab();

    qDebug() << "ProductionDialog::selectionChangedNotesTable() - Exit!";
}

void ProductionDialog::updateNotesTab()
{
    qDebug() << "ProductionDialog::updateNotesTab()!";

    bool noteFounded = false;

    for (int i = 0; i < m_notesList.size(); ++i)
    {
        if (m_noteSelected == m_notesList.at(i)->getId())
        {
            noteFounded = true;
            qDebug() << "ProductionDialog::selectionChangedNotesTable() - Note founded!";

            ui->textNoteEdit->setPlainText(m_notesList.at(i)->getText());

            uint creationAuthor = m_notesList.at(i)->getCreationEmployee();
            for (int j = 0; j < m_employeesList.size(); ++j)
            {
                if (creationAuthor == m_employeesList.at(j)->getId())
                {
                    ui->authorNoteCreEdit->setText(m_employeesList.at(j)->getSurname() + " " +
                                                   m_employeesList.at(j)->getName());
                    qDebug() << "ProductionDialog::selectionChangedNotesTable() - Note creation author" <<
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
                    qDebug() << "ProductionDialog::selectionChangedNotesTable() - Note modification author" <<
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

void ProductionDialog::keyPressEvent(QKeyEvent* e)
{
    qDebug() << "ProductionDialog::keyPressEvent()";
    if(e->key() == Qt::Key_Escape) noApply();
}
