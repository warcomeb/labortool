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

#include "notedialog.h"
#include "ui_notedialog.h"

#include "metadata.h"

#include <QDebug>
#include <QMessageBox>

NoteDialog::NoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteDialog),
    m_parentId(0)
{   
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION) + " - Activity Note Dialog");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(noApply()));

}

NoteDialog::~NoteDialog()
{
    if (m_note)
        delete m_note;

    delete ui;
}

void NoteDialog::translateUi()
{
    ui->retranslateUi(this);
}


void NoteDialog::apply()
{
    qDebug() << "NoteDialog::apply()";

    saveValues();

    if (m_note != 0)
    {
        close();
    }
}

void NoteDialog::noApply()
{
    qDebug() << "NoteDialog::noApply()";

    m_note = 0;
    close();
}

void NoteDialog::setupDialog()
{
    qDebug() << "NoteDialog::setupDialog()";

    switch (m_openType)
    {
    case Add:
        ui->textEdit->setEnabled(true);
        ui->textEdit->setPlainText("");
        break;
    case Edit:
        ui->textEdit->setEnabled(true);
        break;
    }

    qDebug() << "NoteDialog::setupDialog() - Exit!";
}

void NoteDialog::saveValues ()
{
    qDebug() << "NoteDialog::saveValues()";

    if (ui->textEdit->toPlainText().isEmpty())
    {
        qDebug() << "NoteDialog::saveValues() - Text is empty";
        QMessageBox::critical(this, tr("Error"),
            tr("Note text is empty!"));
        return;
    }

    switch (m_openType)
    {
    case Add:
        m_note = new Note(ui->textEdit->toPlainText(),m_parentId,m_parentType,m_author);
        break;
    case Edit:
        m_note->setText(ui->textEdit->toPlainText());
        m_note->setModificationInformation(m_author,QDateTime::currentDateTime());
        break;
    }

    qDebug() << "NoteDialog::saveValues() - Exit!";
}

Note* NoteDialog::getSavedNote()
{
    qDebug() << "NoteDialog::getSavedNote()";

    if (m_note)
        return m_note;
    else
        return 0;
}

void NoteDialog::setOpenType (DialogType type)
{
    qDebug() << "NoteDialog::setOpenType()";

    m_openType = type;
    setupDialog();

    qDebug() << "NoteDialog::setOpenType() - Exit!";
}

void NoteDialog::setParentType (Note::ParentType type)
{
    m_parentType = type;
}

void NoteDialog::prepareNewNote (uint parentId, Employee* const author)
{
    qDebug() << "NoteDialog::prepareNewNote()";

    Q_ASSERT(m_openType == NoteDialog::Add);

    m_parentId = parentId;
    m_author = author;

    qDebug() << "NoteDialog::prepareNewNote() - Exit!";
}

void NoteDialog::setSelectedNote (Note * note, Employee* const author)
{
    qDebug() << "NoteDialog::setSelectedNote()";

    m_note = note;
    m_author = author;

    Q_ASSERT(m_openType != NoteDialog::Add);

    fillNoteField();

    qDebug() << "NoteDialog::setSelectedNote() - Exit!";
}

void NoteDialog::fillNoteField()
{
    qDebug() << "NoteDialog::fillNoteField()";
    ui->textEdit->setPlainText(m_note->getText());
    qDebug() << "NoteDialog::fillNoteField() - Exit";
}
