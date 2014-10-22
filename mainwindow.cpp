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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "metadata.h"

#include <QDebug>

#define DB_TYPE "QMYSQL"
#define DB_NAME "labortool"
#define DB_USER "root"
#define DB_PASS "scossa"
#define DB_HOST "localhost"
#define DB_PORT 3306

#define MAINWINDOW_TAB_HOME         0
#define MAINWINDOW_TAB_ACTIVITY     1
#define MAINWINDOW_TAB_EMPLOYEE     2


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_employeeSelected(-1),
    m_activitySelected(-1)
{
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION));
    setFocusPolicy(Qt::StrongFocus);

    initBasicCommand();

    connectToDatabase();

    /* Initialize each controller */
    m_employeeController = new EmployeeController(&m_database);
    initEmployeeTab();
    m_activityController = new ActivityController(&m_database);
    initActivityTab();

    m_loginController = new LoginController(&m_database);



    /* Update data into tab when it was selected!! */
    /* TODO: Add waiting... */
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),
            this,SLOT(updateSelectedTab(int)));

    /* Connect Login button to specific slot */
    connect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogin()));
    connect(m_loginController,SIGNAL(loggedUser(Employee*)),
            this,SLOT(loggedUser(Employee*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSelectedTab (int index)
{
    qDebug() << "Selected Tab:" << index;

    switch (index)
    {
    case MAINWINDOW_TAB_HOME:
        break;
    case MAINWINDOW_TAB_ACTIVITY:
        break;
    case MAINWINDOW_TAB_EMPLOYEE:
        break;
    }
}

bool MainWindow::connectToDatabase ()
{

    /* FIXME: Questi sono tutti dati da correggere da file di configurazione! */
    m_database = QSqlDatabase::addDatabase( DB_TYPE );
    m_database.setDatabaseName( DB_NAME );
    m_database.setUserName( DB_USER );
    m_database.setPassword( DB_PASS );
    m_database.setHostName( DB_HOST );
    m_database.setPort( DB_PORT );
    /* FIXME: questa stringa non può andare bene, deve essere universale!!! */
    //m_database.setConnectOptions("UNIX_SOCKET=/Applications/mampstack-5.4.26-0/mysql/tmp/mysql.sock");

    if ( !m_database.open() )
    {
        qDebug() << "Database not connected!";
        qDebug() << m_database.lastError();
        return false;
    }
    qDebug() << "Database connected!";
    return true;
}

bool MainWindow::disconnectToDatabase()
{

}

void MainWindow::initBasicCommand()
{
    ui->loginLabel->setText(tr("Welcome unknown User!"));
}

/**
 * @brief MainWindow::initActivityTab
 *
 * Questo metodo collega tutti i segnali del tab activity ai
 * relativi gestori.
 */
void MainWindow::initActivityTab()
{
    connect(ui->addActivityButton,SIGNAL(clicked()),
            this,SLOT(openActivityDialog()));

    connect(ui->viewActivityButton,SIGNAL(clicked()),
            this,SLOT(openActivityDialog()));

    connect(ui->editActivityButton,SIGNAL(clicked()),
            this,SLOT(openActivityDialog()));

    connect(ui->deleteActivityButton,SIGNAL(clicked()),
            this,SLOT(openActivityDialog()));

//    connect(ui->searchActivityButton,SIGNAL(clicked()),
//            this,SLOT(searchActivities()));
//    connect(ui->searchActivityResetButton,SIGNAL(clicked()),
//            this,SLOT(resetSearchActivities()));

    /* Update table slots */
    connect(m_activityController,SIGNAL(updatedActivitiesList(QStringList)),
            this,SLOT(updateActivitiesTable(QStringList)));

    /* Startup table! */
    m_activityModel = new QStandardItemModel(1, 7);
    ui->activityTable->setModel(m_activityModel);
    ui->activityTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->activityTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(selectionChangedActivitiesTable(const QItemSelection &, const QItemSelection &)));


    QStringList searchParams;
    searchParams << "Status$NotStarted|InProgress|Waiting";
    updateActivitiesTable(searchParams);
}

/**
 * @brief MainWindow::initEmployeeTab
 *
 * Questo metodo collega tutti i segnali del tab employee ai
 * relativi gestori.
 */
void MainWindow::initEmployeeTab()
{
    connect(ui->addEmployeeButton,SIGNAL(clicked()),
            this,SLOT(openEmployeeDialog()));

    connect(ui->viewEmployeeButton,SIGNAL(clicked()),
            this,SLOT(openEmployeeDialog()));

    connect(ui->editEmployeeButton,SIGNAL(clicked()),
            this,SLOT(openEmployeeDialog()));

    connect(ui->searchEmployeeButton,SIGNAL(clicked()),
            this,SLOT(searchEmployees()));
    connect(ui->searchEmployeeResetButton,SIGNAL(clicked()),
            this,SLOT(resetSearchEmployees()));

    /* Fill search combo box */
    ui->searchEmployeeRoleCombobox->clear();
    ui->searchEmployeeRoleCombobox->addItem(tr("All"), -1);
    ui->searchEmployeeRoleCombobox->addItem(tr("Coordinator"), Employee::Coordinator);
    ui->searchEmployeeRoleCombobox->addItem(tr("Senior Designer"), Employee::SeniorDesigner);
    ui->searchEmployeeRoleCombobox->addItem(tr("Designer"), Employee::Designer);
    ui->searchEmployeeRoleCombobox->addItem(tr("Technician"), Employee::Technician);
    ui->searchEmployeeRoleCombobox->addItem(tr("Student"), Employee::Student);

    ui->searchEmployeeCompanyCombobox->clear();
    ui->searchEmployeeCompanyCombobox->addItem(tr("All"), -1);
    ui->searchEmployeeCompanyCombobox->addItem(tr("AEA"), Employee::Aea);
    ui->searchEmployeeCompanyCombobox->addItem(tr("General Impianti"), Employee::Gi);
    ui->searchEmployeeCompanyCombobox->addItem(tr("Extern"), Employee::Extern);

    ui->searchEmployeeActiveCombobox->clear();
    ui->searchEmployeeActiveCombobox->addItem(tr("All"), -1);
    ui->searchEmployeeActiveCombobox->addItem(tr("Yes"), Employee::Yes);
    ui->searchEmployeeActiveCombobox->addItem(tr("No"), Employee::No);

    /* Update table slots */
    connect(m_employeeController,SIGNAL(updatedEmployeesList(QStringList)),
            this,SLOT(updateEmployeesTable(QStringList)));

    /* Startup table! */
    m_employeeModel = new QStandardItemModel(1, 5);
    ui->employeeTable->setModel(m_employeeModel);
    ui->employeeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->employeeTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(selectionChangedEmployeesTable(const QItemSelection &, const QItemSelection &)));

    QStringList searchParams;
    searchParams << "Active=Yes";
    updateEmployeesTable(searchParams);
}

/**
 * @brief MainWindow::openActivityDialog
 *
 * Questo slot permette di aprire la finestra di
 * editing delle attività, configurandola in base al
 * pulsante che ne ha richiesto l'aperura: add, edit,
 * view e delete.
 */
void MainWindow::openActivityDialog()
{
    qDebug() << "MainWindow::openActivityDialog()";
    QStringList searchParams;
    QVector<QVector<QString> > employeesList;

    if (sender() == ui->addActivityButton)
    {
        searchParams << "Active=Yes";
        employeesList = m_employeeController->getEmployeesList(searchParams);

        m_activityController->openAddActivityDialog(employeesList);
    }
    else if (sender() == ui->viewActivityButton)
    {
        employeesList = m_employeeController->getEmployeesList(searchParams);

        m_activityController->openViewActivityDialog(m_activitySelected,employeesList);
    }
    else if (sender() == ui->editActivityButton)
    {
        employeesList = m_employeeController->getEmployeesList(searchParams);

        m_activityController->openEditActivityDialog(m_activitySelected,employeesList);
    }
    else if (sender() == ui->deleteActivityButton)
    {
        /* TODO */
    }
}

/**
 * @brief MainWindow::openEmployeeDialog
 *
 * Questo slot permette di aprire la finestra di
 * editing dei collaboratori, configurandola in base al
 * pulsante che ne ha richiesto l'aperura: add, edit e
 * view.
 */
void MainWindow::openEmployeeDialog()
{
    qDebug() << "MainWindow::openEmployeeDialog()";

    if (sender() == ui->addEmployeeButton)
    {
        m_employeeController->openAddEmployeeDialog();
    }
    else if (sender() == ui->viewEmployeeButton)
    {
        m_employeeController->openViewEmployeeDialog(m_employeeSelected);
    }
    else if (sender() == ui->editEmployeeButton)
    {
        m_employeeController->openEditEmployeeDialog(m_employeeSelected);
    }
}

void MainWindow::selectionChangedEmployeesTable(const QItemSelection & sel,
                                                const QItemSelection & des)
{
    qDebug() << "MainWindow::selectionChangedEmployeesTable()";
    QModelIndexList indexes = sel.indexes();
    //QModelIndexList indexes = ui->employeeTable->selectionModel()->selection().indexes();
    qDebug() << "MainWindow::selectionChangedEmployeesTable() - selected number" << indexes.count();
    if (indexes.count() != 1 )
    {
        m_employeeSelected = -1;
        qDebug() << "MainWindow::selectionChangedEmployeesTable() - Too many items selected";
        return;
    }

    qDebug() << "MainWindow::selectionChangedEmployeesTable() - row selected" << indexes.at(0).row();
    m_employeeSelected = m_employeeModel->item(indexes.at(0).row(),0)->text().toInt();
}

void MainWindow::updateEmployeesTable(QStringList searchParams)
{
    qDebug() << "MainWindow::updateEmployeesTable()";

    m_employeeModel->clear();
    m_employeeModel->setColumnCount(5);
    m_employeeModel->sort(1,Qt::AscendingOrder);

    m_employeeModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_employeeModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Surname"));
    m_employeeModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Name"));
    m_employeeModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Username"));
    m_employeeModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Role"));

    QVector<QVector<QString> > employeesList =
            m_employeeController->getEmployeesList(searchParams);

    qDebug() << "MainWindow::updateEmployeesTable() - Employees size:" << employeesList.size();
    if (employeesList.size()>0)
    {
        for (int row = 0; row < employeesList.size(); ++row)
        {
            for (int column = 0; column < 5; ++column)
            {
                QStandardItem *item = new QStandardItem(employeesList.at(row).at(column));
                m_employeeModel->setItem(row, column, item);
            }
        }
    }
}

void MainWindow::searchEmployees()
{
    qDebug() << "MainWindow::searchEmployees()";
    QStringList searchParams;

    if (!ui->searchEmployeeText->text().isEmpty())
    {
        QString text = "Text%" + ui->searchEmployeeText->text();
        qDebug() << "MainWindow::searchEmployees() - String" << text;
        searchParams << text;
    }

    if (ui->searchEmployeeRoleCombobox->currentData().toInt() != -1)
    {
        QString role = "Role=";
        role.append(Employee::getRoleString(
            static_cast<Employee::Role>(ui->searchEmployeeRoleCombobox->currentData().toInt()))
        );
        qDebug() << "MainWindow::searchEmployees() - Role" << role ;
        searchParams << role;
    }

    if (ui->searchEmployeeActiveCombobox->currentData().toInt() != -1)
    {
        QString active = "Active=";
        active.append(Employee::getActiveStatusString(
            static_cast<Employee::Active>(ui->searchEmployeeActiveCombobox->currentData().toInt()))
        );
        qDebug() << "MainWindow::searchEmployees() - Active" << active ;
        searchParams << active;
    }

    if (ui->searchEmployeeCompanyCombobox->currentData().toInt() != -1)
    {
        QString company = "Company=";
        company.append(Employee::getCompanyString(
            static_cast<Employee::Company>(ui->searchEmployeeCompanyCombobox->currentData().toInt()))
        );
        qDebug() << "MainWindow::searchEmployees() - Company" << company ;
        searchParams << company;
    }

    qDebug() << "MainWindow::searchEmployees() - update table";
    updateEmployeesTable(searchParams);
}

void MainWindow::resetSearchEmployees()
{
    qDebug() << "MainWindow::resetSearchEmployees()";
    QStringList searchParams;
    searchParams << "Active=Yes";

    ui->searchEmployeeText->setText("");
    ui->searchEmployeeRoleCombobox->setCurrentIndex(0);
    ui->searchEmployeeCompanyCombobox->setCurrentIndex(0);
    ui->searchEmployeeActiveCombobox->setCurrentIndex(0);

    qDebug() << "MainWindow::resetSearchEmployees() - update table";
    updateEmployeesTable(searchParams);
}

void MainWindow::selectionChangedActivitiesTable(const QItemSelection & sel,
                                                const QItemSelection & des)
{
    qDebug() << "MainWindow::selectionChangedActivitiesTable()";
    QModelIndexList indexes = sel.indexes();
    qDebug() << "MainWindow::selectionChangedActivitiesTable() - selected number" << indexes.count();
    if (indexes.count() != 1 )
    {
        m_activitySelected = -1;
        qDebug() << "MainWindow::selectionChangedActivitiesTable() - Too many items selected";
        return;
    }

    qDebug() << "MainWindow::selectionChangedActivitiesTable() - row selected" << indexes.at(0).row();
    m_activitySelected = m_activityModel->item(indexes.at(0).row(),0)->text().toInt();
}

void MainWindow::updateActivitiesTable(QStringList searchParams)
{
    qDebug() << "MainWindow::updateActivitiesTable()";

    QDate shortDeadline = QDate::currentDate().addDays(7);
    bool isShortDeadline = false;
    qDebug() << "MainWindow::updateActivitiesTable() - short deadline" << shortDeadline;
    QDate mediumDeadline = QDate::currentDate().addDays(21);
    bool isMediumDeadline = false;
    qDebug() << "MainWindow::updateActivitiesTable() - medium deadline" << mediumDeadline;

    m_activityModel->clear();
    m_activityModel->setColumnCount(7);
//    m_activityModel->sort(1,Qt::AscendingOrder);

    m_activityModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_activityModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    m_activityModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Workcode"));
    m_activityModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Employee"));
    m_activityModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Priority"));
    m_activityModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Status"));
    m_activityModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Type"));

    QVector<QVector<QString> > activitiesList =
            m_activityController->getActivitiesList(searchParams);

    qDebug() << "MainWindow::updateActivitiesTable() - Activities size:" << activitiesList.size();
    if (activitiesList.size()>0)
    {
        /* Get the employees list */
        QStringList employeesSearchParams;
        employeesSearchParams << "Active=Yes";
        QVector<QVector<QString> > employeesList =
                m_employeeController->getEmployeesList(employeesSearchParams);
        qDebug() << "MainWindow::updateActivitiesTable() - Employees size:" << employeesList.size();


        for (int row = 0; row < activitiesList.size(); ++row)
        {
            qDebug() << "MainWindow::updateActivitiesTable() - db deadline" << activitiesList.at(row).at(7);
            QDate deadline = QDate::fromString(activitiesList.at(row).at(7),"yyyy-MM-dd");
            qDebug() << "MainWindow::updateActivitiesTable() - deadline" << deadline;

            if (deadline < shortDeadline)
            {
                isShortDeadline = true;
                qDebug() << "MainWindow::updateActivitiesTable() - less than 7 days!";
            }
            else if (deadline < mediumDeadline)
            {
                isMediumDeadline = true;
                qDebug() << "MainWindow::updateActivitiesTable() - less then 21 days!";
            }

            for (int column = 0; column < 7; ++column)
            {
                QStandardItem *item;

                if (column == 3) // Employee
                {
                    uint employeeId = activitiesList.at(row).at(column).toUInt();
                    for (int i = 0; i < employeesList.size(); ++i)
                    {
                        uint searchEmployeeId = employeesList.at(i).at(0).toUInt();
                        if (employeeId == searchEmployeeId)
                        {
                            item = new QStandardItem(
                                employeesList.at(i).at(1) + " " + employeesList.at(i).at(2)
                            );
                            break;
                        }
                    }
                }
                else
                {
                    item = new QStandardItem(activitiesList.at(row).at(column));
                }

                if (isShortDeadline)
                    item->setBackground(QBrush(Qt::red));
                else if (isMediumDeadline)
                    item->setBackground(QBrush(Qt::yellow));

                m_activityModel->setItem(row, column, item);
            }

            isMediumDeadline = false;
            isShortDeadline = false;
        }
    }
}

void MainWindow::searchActivities()
{
    qDebug() << "MainWindow::searchActivities()";
    QStringList searchParams;
}

void MainWindow::resetSearchActivities()
{
    qDebug() << "MainWindow::resetSearchActivities()";

}

void MainWindow::userLogin()
{
    qDebug() << "MainWindow::userLogin()";
    m_loginController->openDialog();
    qDebug() << "MainWindow::userLogin() - Exit!";
}

void MainWindow::userLogout()
{
    qDebug() << "MainWindow::userLogout()";

    ui->loginLabel->setText(tr("Welcome unknown User!"));

    disconnect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogout()));
    ui->loginButton->setText(tr("Login"));
    connect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogin()));

    qDebug() << "MainWindow::userLogout() - Exit!";
}

void MainWindow::loggedUser(Employee *employee)
{
    qDebug() << "MainWindow::loggedUser()";

    ui->loginLabel->setText(
        tr("Welcome ") + employee->getName() + " " + employee->getSurname() + "!");

    disconnect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogin()));
    ui->loginButton->setText(tr("Logout"));
    connect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogout()));

    qDebug() << "MainWindow::loggedUser() - Exit!";
}
