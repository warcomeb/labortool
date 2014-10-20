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

#include "logindialog.h"
#include "ui_logindialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>

#include "metadata.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION) + " - Login Dialog");
    ui->statusText->setText(tr("Enter username and password"));

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(controlData()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::controlData()
{
    qDebug() << "LoginDialog::controlData()";

    QByteArray hash;
    QRegExp nick = QRegExp(QString::fromUtf8("[a-zA-Z0-9]{6,20}"));

    qDebug() << "LoginDialog::controlData() - test username";
    if (nick.exactMatch(ui->usernameText->text()))
    {
        qDebug() << "LoginDialog::controlData() - Username correct:" << ui->usernameText->text();
        m_username = ui->usernameText->text();
    }
    else
    {
        qDebug() << "LoginDialog::controlData() - Username not correct:" << ui->usernameText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Username not correct!"));
        m_username = "";
        return;
    }

    qDebug() << "LoginDialog::controlData() - test password";
    if (nick.exactMatch(ui->passwordText->text()))
    {
        qDebug() << "LoginDialog::controlData() - Password correct:" << ui->passwordText->text();

        hash.append(ui->passwordText->text());
        hash = QCryptographicHash::hash(hash,QCryptographicHash::Sha1);
//        qDebug() << "LoginDialog::controlData() - The hashed byte array:" << hash;
        m_password = QString(hash.toHex());
        qDebug() << "LoginDialog::controlData() - The hashed password:" << m_password.toUtf8();
    }
    else
    {
        qDebug() << "LoginDialog::controlData() - Password not correct:" << ui->passwordText->text();
        QMessageBox::critical(this, tr("Error"),
            tr("Password not correct!"));
        m_password = "";
        return;
    }

    emit dataReady();
}
