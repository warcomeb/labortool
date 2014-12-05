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

#include "activitynotedialog.h"
#include "ui_activitynotedialog.h"

#include "metadata.h"

#include <QDebug>
#include <QMessageBox>

ActivityNoteDialog::ActivityNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivityNoteDialog)
{   
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION) + " - Activity Note Dialog");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(noApply()));

}

ActivityNoteDialog::~ActivityNoteDialog()
{
    if (m_activityNote)
        delete m_activityNote;

    delete ui;
}

void ActivityNoteDialog::apply()
{
    qDebug() << "ActivityNoteDialog::apply()";

//    if (m_openType != ActivityNoteDialog::View)
    saveValues ();

    if (m_activityNote != 0)
    {
        close();
    }
}

void ActivityNoteDialog::noApply()
{
    qDebug() << "ActivityNoteDialog::noApply()";

//    if (m_openType != ActivityNoteDialog::View)
    m_activityNote = 0;
    close();
}

//void ActivityNoteDialog::currentAuthor


void ActivityNoteDialog::setupDialog()
{
    qDebug() << "ActivityNoteDialog::setupDialog()";

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

    qDebug() << "ActivityNoteDialog::setupDialog() - Exit!";
}

void ActivityNoteDialog::saveValues ()
{
    qDebug() << "ActivityNoteDialog::saveValues()";

    if (ui->textEdit->toPlainText().isEmpty())
    {
        qDebug() << "ActivityNoteDialog::saveValues() - Text is empty";
        QMessageBox::critical(this, tr("Error"),
            tr("Activity note text is empty!"));
        return;
    }

    switch (m_openType)
    {
    case Add:
        m_activityNote = new ActivityNote(ui->textEdit->toPlainText(),m_activity,m_author);
        break;
    case Edit:
        m_activityNote->setText(ui->textEdit->toPlainText());
        m_activityNote->setModificationInformation(m_author,QDateTime::currentDateTime());
        break;
    }

    qDebug() << "ActivityNoteDialog::saveValues() - Exit!";
}

ActivityNote* ActivityNoteDialog::getSavedActivityNote()
{
    qDebug() << "ActivityNoteDialog::getSavedActivityNote()";

    if (m_activityNote)
        return m_activityNote;
    else
        return 0;
}

void ActivityNoteDialog::setOpenType (DialogType type)
{
    qDebug() << "ActivityNoteDialog::setOpenType()";

    m_openType = type;
    setupDialog();

    qDebug() << "ActivityNoteDialog::setOpenType() - Exit!";
}

void ActivityNoteDialog::setOwners (Activity* activity, Employee* const author)
{
    qDebug() << "ActivityNoteDialog::setOwners()";
    m_activity = activity;
    m_author = author;
    qDebug() << "ActivityNoteDialog::setOwners() - Author"  << m_author->getName() << m_author->getSurname();
    qDebug() << "ActivityNoteDialog::setOwners() - Exit!";
}

void ActivityNoteDialog::setSelectedActivityNote (ActivityNote * note, Employee* const author)
{
    qDebug() << "ActivityNoteDialog::setSelectedActivityNote()";

    m_activityNote = note;
    m_author = author;

    Q_ASSERT(m_openType != ActivityNoteDialog::Add);

    fillNoteField();

    qDebug() << "ActivityNoteDialog::setSelectedActivityNote() - Exit!";
}

void ActivityNoteDialog::fillNoteField()
{
    qDebug() << "ActivityNoteDialog::fillNoteField()";
    ui->textEdit->setPlainText(m_activityNote->getText());
    qDebug() << "ActivityNoteDialog::fillNoteField() - Exit";
}
