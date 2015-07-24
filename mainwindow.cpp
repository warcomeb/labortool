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
#include <QMessageBox>

#define DB_TYPE "QMYSQL"
#define DB_NAME "labortool"
#define DB_USER "root"
#define DB_PASS "scossa"
#define DB_HOST "localhost"
#define DB_PORT 3306

#define MAINWINDOW_TAB_HOME         0
#define MAINWINDOW_TAB_ACTIVITY     1
#define MAINWINDOW_TAB_PRODUCTION   2
#define MAINWINDOW_TAB_EMPLOYEE     3

QColor MainWindow::m_colorWarning   = QColor::fromRgb(255,255,0,150);
QColor MainWindow::m_colorDanger    = QColor::fromRgb(255,0,0,150);
QColor MainWindow::m_colorEnded     = QColor::fromRgb(0,255,0,150);
QColor MainWindow::m_colorNoProblem = QColor::fromRgb(255,255,255,0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_employeeLogged(0),
    m_employeeSelected(0),
    m_activitySelected(0),
    m_productionSelected(0),
    m_isInitEmployeeTab(false),
    m_isInitActivityTab(false),
    m_isInitProductionTab(false)
{
    ui->setupUi(this);

    setWindowTitle(QString(PROJECT_NAME) + " v." + QString(PROJECT_VERSION));
    setFocusPolicy(Qt::StrongFocus);

    readConfigurationFile();

    createLanguageMenu();

    initBasicCommand();

//    connectToDatabase();

    /* Initialize each controller */
    m_employeeController = new EmployeeController(&m_database);
    initEmployeeTab();
    m_activityController = new ActivityController(&m_database);
    initActivityTab();
    m_productionController = new ProductionController(&m_database);
    initProductionTab();

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
    /* Update all observer for this event */
    connect(this,SIGNAL(changedLoggedUser()),
            this,SLOT(updateLoggedUser()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readConfigurationFile()
{
    qDebug() << "MainWindow::readConfigurationFile()";

    if (m_configurationGeneral)
    {
        m_configurationGeneral = new QSettings("config/config.ini", QSettings::IniFormat);
        connectToDatabase();
    }
    else
    {
        qDebug() << "MainWindow::readConfigurationFile() - Configuration file just loaded!";
    }

//    QString specificFileName = m_configurationGeneral->value("loadedfile").toString();

//    if (!specificFileName.isEmpty())
//    {
//        qDebug() << "MainWindow::readConfigurationFile() - Loaded file:" << specificFileName;

//        m_configurationSpecific = new QSettings(specificFileName, QSettings::IniFormat);
//        connectToDatabase();

//        /* TODO: update tabelle */
//    }
//    else
//    {
//        qDebug() << "MainWindow::readConfigurationFile() - There isn't loaded file!";
//    }
}

void MainWindow::updateSelectedTab (int index)
{
    qDebug() << "MainWindow::updateSelectedTab() - Selected tab:" <<  index;

    switch (index)
    {
    case MAINWINDOW_TAB_HOME:
        break;
    case MAINWINDOW_TAB_ACTIVITY:
        break;
    case MAINWINDOW_TAB_PRODUCTION:
        break;
    case MAINWINDOW_TAB_EMPLOYEE:
        break;
    }
}

bool MainWindow::connectToDatabase ()
{
    qDebug() << "MainWindow::connectToDatabase()";

    m_database = QSqlDatabase::addDatabase( DB_TYPE );
    m_database.setDatabaseName( m_configurationGeneral->value("database/name").toString() );
    m_database.setUserName( m_configurationGeneral->value("database/username").toString() );
    m_database.setPassword( m_configurationGeneral->value("database/password").toString() );
    m_database.setHostName( m_configurationGeneral->value("database/host").toString() );
    m_database.setPort( m_configurationGeneral->value("database/port").toUInt() );

    /* FIXME: questa stringa non può andare bene, deve essere universale!!! */
    //m_database.setConnectOptions("UNIX_SOCKET=/Applications/mampstack-5.4.26-0/mysql/tmp/mysql.sock");

    if ( !m_database.open() )
    {
        qDebug() << "MainWindow::connectToDatabase() - Database not connected!";
        qDebug() << m_database.lastError();
        return false;
    }
    qDebug() << "MainWindow::connectToDatabase() - Database connected!";
    return true;
}

bool MainWindow::disconnectToDatabase()
{

}

void MainWindow::initBasicCommand()
{
    ui->loginLabel->setText(tr("Welcome unknown User!"));

    /* We want to show the welcome tab! */
    ui->tabWidget->setCurrentIndex(0);

    m_preferencesDialog = new PreferencesDialog;
    connect(ui->actionPreferences,SIGNAL(triggered()),
            this,SLOT(managePreferences()));
}

/**
 * @brief MainWindow::initActivityTab
 *
 * Questo metodo collega tutti i segnali del tab activity ai
 * relativi gestori.
 */
void MainWindow::initActivityTab()
{ 
    qDebug() << "MainWindow::initActivityTab()";

    Q_ASSERT(!m_isInitActivityTab);

    disconnect(ui->addActivityButton,SIGNAL(clicked()),
            this,SLOT(openActivityDialog()));
    ui->addActivityButton->setEnabled(false);

    connect(ui->viewActivityButton,SIGNAL(clicked()),
            this,SLOT(openActivityDialog()));
    ui->viewActivityButton->setEnabled(true);

    disconnect(ui->editActivityButton,SIGNAL(clicked()),
            this,SLOT(openActivityDialog()));
    ui->editActivityButton->setEnabled(false);

    disconnect(ui->deleteActivityButton,SIGNAL(clicked()),
               this,SLOT(openActivityDialog()));
    ui->deleteActivityButton->setEnabled(false);

    disconnect(ui->addNoteActivityButton,SIGNAL(clicked()),
            this,SLOT(openActivityDialog()));
    ui->addNoteActivityButton->setEnabled(false);

    connect(ui->searchActivitytButton,SIGNAL(clicked()),
            this,SLOT(searchActivities()));
    connect(ui->searchActivityResetButton,SIGNAL(clicked()),
            this,SLOT(resetSearchActivities()));


    connect(ui->searchEmployeeButton,SIGNAL(clicked()),
            this,SLOT(searchEmployees()));
    connect(ui->searchEmployeeResetButton,SIGNAL(clicked()),
            this,SLOT(resetSearchEmployees()));

    /* Fill search combo box */
    qDebug() << "MainWindow::initActivityTab() - Fill search combobox";
    ui->searchActivityStatusCombobox->clear();
    ui->searchActivityStatusCombobox->addItem(tr("All"), -1);
    ui->searchActivityStatusCombobox->addItem(tr("All Open"), -2);
    ui->searchActivityStatusCombobox->addItem(tr("Not Started"), Activity::NotStarted);
    ui->searchActivityStatusCombobox->addItem(tr("In Progress"), Activity::InProgress);
    ui->searchActivityStatusCombobox->addItem(tr("Ended"), Activity::Ended);
    ui->searchActivityStatusCombobox->addItem(tr("Postponed"), Activity::Postponed);
    ui->searchActivityStatusCombobox->addItem(tr("Waiting"), Activity::Waiting);

    ui->searchActivityPriorityCombobox->clear();
    ui->searchActivityPriorityCombobox->addItem(tr("All"), -1);
    ui->searchActivityPriorityCombobox->addItem(tr("Low"), Activity::Low);
    ui->searchActivityPriorityCombobox->addItem(tr("Medium"), Activity::Medium);
    ui->searchActivityPriorityCombobox->addItem(tr("High"), Activity::High);
    ui->searchActivityPriorityCombobox->addItem(tr("Now"), Activity::Now);

    ui->searchActivityTypeCombobox->clear();
    ui->searchActivityTypeCombobox->addItem(tr("All"), -1);
    ui->searchActivityTypeCombobox->addItem(tr("Board"), Activity::Board);
    ui->searchActivityTypeCombobox->addItem(tr("Repair"), Activity::Repair);
    ui->searchActivityTypeCombobox->addItem(tr("Support"), Activity::Support);
    ui->searchActivityTypeCombobox->addItem(tr("Firmware"), Activity::Firmware);
    ui->searchActivityTypeCombobox->addItem(tr("Production"), Activity::Production);

    QStringList searchEmployeeParams;
    QVector<Employee*> employeesList =
            m_employeeController->getEmployeesList(searchEmployeeParams);

    qDebug() << "MainWindow::initActivityTab() - Fill search employee combobox";
    ui->searchActivityEmployeeCombobox->clear();
    ui->searchActivityEmployeeCombobox->addItem(tr("All"), -1);
    if (employeesList.size()>0)
    {
        for (int row = 0; row < employeesList.size(); ++row)
        {
            ui->searchActivityEmployeeCombobox->addItem((employeesList.at(row))->getSurname() + " " +
                                                        (employeesList.at(row))->getName(),
                                                        (employeesList.at(row))->getId());
        }
    }


    /* Update table slots */
    connect(m_activityController,SIGNAL(updatedActivitiesList(QStringList)),
            this,SLOT(updateActivitiesTable(QStringList)));

    /* Startup table! */
    m_activityModel = new QStandardItemModel(1, 7);
    ui->activityTable->setModel(m_activityModel);
    ui->activityTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->activityTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(selectionChangedActivitiesTable(const QItemSelection &, const QItemSelection &)));


    QStringList searchParams;
    searchParams << "Status$NotStarted|InProgress|Waiting";
    updateActivitiesTable(searchParams);
}

/**
 * @brief MainWindow::initProductionTab
 *
 * Questo metodo collega tutti i segnali del tab production ai
 * relativi gestori.
 */
void MainWindow::initProductionTab()
{
    qDebug() << "MainWindow::initProductionTab()";

    Q_ASSERT(!m_isInitProductionTab);

    disconnect(ui->addProductionButton,SIGNAL(clicked()),
            this,SLOT(openProductionDialog()));
    ui->addProductionButton->setEnabled(false);

    connect(ui->viewProductionButton,SIGNAL(clicked()),
            this,SLOT(openProductionDialog()));
    ui->viewProductionButton->setEnabled(true);

    disconnect(ui->editProductionButton,SIGNAL(clicked()),
            this,SLOT(openProductionDialog()));
    ui->editProductionButton->setEnabled(false);

    disconnect(ui->deleteProductionButton,SIGNAL(clicked()),
            this,SLOT(openProductionDialog()));
    ui->deleteProductionButton->setEnabled(false);

    disconnect(ui->addNoteProductionButton,SIGNAL(clicked()),
            this,SLOT(openProductionDialog()));
    ui->addNoteProductionButton->setEnabled(false);

    connect(ui->searchProductionButton,SIGNAL(clicked()),
            this,SLOT(searchProductions()));
    connect(ui->searchProductionResetButton,SIGNAL(clicked()),
            this,SLOT(resetSearchProductions()));

    /* Fill search combo box */
    qDebug() << "MainWindow::initProductionTab() - Fill search combobox";
    ui->searchProductionStatusCombobox->clear();
    ui->searchProductionStatusCombobox->addItem(tr("All"), -1);
    ui->searchProductionStatusCombobox->addItem(tr("All Open"), -2);
    ui->searchProductionStatusCombobox->addItem(tr("Not Started"), Activity::NotStarted);
    ui->searchProductionStatusCombobox->addItem(tr("In Progress"), Activity::InProgress);
    ui->searchProductionStatusCombobox->addItem(tr("Ended"), Activity::Ended);
    ui->searchProductionStatusCombobox->addItem(tr("Postponed"), Activity::Postponed);
    ui->searchProductionStatusCombobox->addItem(tr("Waiting"), Activity::Waiting);

    QStringList searchEmployeeParams;
    QVector<Employee*> employeesList =
            m_employeeController->getEmployeesList(searchEmployeeParams);

    qDebug() << "MainWindow::initProductionTab() - Fill search employee combobox";
    ui->searchProductionEmployeeCombobox->clear();
    ui->searchProductionEmployeeCombobox->addItem(tr("All"), -1);
    if (employeesList.size()>0)
    {
        for (int row = 0; row < employeesList.size(); ++row)
        {
            ui->searchProductionEmployeeCombobox->addItem((employeesList.at(row))->getSurname() + " " +
                                                          (employeesList.at(row))->getName(),
                                                          (employeesList.at(row))->getId());
        }
    }



    /* Update table slots */
    connect(m_productionController,SIGNAL(updatedProductionsList(QStringList)),
            this,SLOT(updateProductionsTable(QStringList)));

    /* Startup table! */
    m_productionModel = new QStandardItemModel(1, 7);
    ui->productionTable->setModel(m_productionModel);
    ui->productionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->productionTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(selectionChangedProductionsTable(const QItemSelection &, const QItemSelection &)));


    QStringList searchParams;
    searchParams << "Status$NotStarted|InProgress|Waiting";
    updateProductionsTable(searchParams);
}

/**
 * @brief MainWindow::initEmployeeTab
 *
 * Questo metodo collega tutti i segnali del tab employee ai
 * relativi gestori.
 */
void MainWindow::initEmployeeTab()
{
    Q_ASSERT(!m_isInitEmployeeTab);

    disconnect(ui->addEmployeeButton,SIGNAL(clicked()),
               this,SLOT(openEmployeeDialog()));
    ui->addEmployeeButton->setEnabled(false);

    connect(ui->viewEmployeeButton,SIGNAL(clicked()),
            this,SLOT(openEmployeeDialog()));
    ui->viewEmployeeButton->setEnabled(true);

    disconnect(ui->editEmployeeButton,SIGNAL(clicked()),
               this,SLOT(openEmployeeDialog()));
    ui->editEmployeeButton->setEnabled(false);


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
    ui->employeeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->employeeTable->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,
            SLOT(selectionChangedEmployeesTable(const QItemSelection &, const QItemSelection &)));

    QStringList searchParams;
    searchParams << "Active=Yes";
    updateEmployeesTable(searchParams);

    m_isInitEmployeeTab = true;
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
    QVector<Employee*> employeesList;

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
        m_activityController->openDeleteActivityDialog(m_activitySelected);
    }
    else if (sender() == ui->addNoteActivityButton)
    {
        Q_ASSERT(m_employeeLogged != 0);

        m_activityController->openAddNoteActivityDialog(m_activitySelected);
    }
}

/**
 * @brief MainWindow::openProductionDialog
 *
 * Questo slot permette di aprire la finestra di
 * editing delle produzioni, configurandola in base al
 * pulsante che ne ha richiesto l'aperura: add, edit,
 * view e delete.
 */
void MainWindow::openProductionDialog()
{
    qDebug() << "MainWindow::openProductionDialog()";
    QStringList searchParams;
    QVector<Employee*> employeesList;

    if (sender() == ui->addProductionButton)
    {
        searchParams << "Active=Yes";
        employeesList = m_employeeController->getEmployeesList(searchParams);

        m_productionController->openAddProductionDialog(employeesList);
    }
    else if (sender() == ui->viewProductionButton)
    {
        employeesList = m_employeeController->getEmployeesList(searchParams);

        m_productionController->openViewProductionDialog(m_productionSelected,employeesList);
    }
    else if (sender() == ui->editProductionButton)
    {
        employeesList = m_employeeController->getEmployeesList(searchParams);

        m_productionController->openEditProductionDialog(m_productionSelected,employeesList);
    }
    else if (sender() == ui->deleteProductionButton)
    {
        m_productionController->openDeleteProductionDialog(m_productionSelected);
    }
    else if (sender() == ui->addNoteProductionButton)
    {
        Q_ASSERT(m_employeeLogged != 0);

        m_productionController->openAddNoteProductionDialog(m_productionSelected);
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

//    if (indexes.count() != 1 )
//    {
//        m_employeeSelected = -1;
//        qDebug() << "MainWindow::selectionChangedEmployeesTable() - Too many items selected";
//        return;
//    }

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

    QVector<Employee*> employeesList =
            m_employeeController->getEmployeesList(searchParams);

    qDebug() << "MainWindow::updateEmployeesTable() - Employees size:" << employeesList.size();
    if (employeesList.size()>0)
    {
        for (int row = 0; row < employeesList.size(); ++row)
        {
            QStandardItem *item;

            item = new QStandardItem(QString::number(employeesList.at(row)->getId()));
            m_employeeModel->setItem(row,0,item);

            item = new QStandardItem(employeesList.at(row)->getSurname());
            m_employeeModel->setItem(row,1,item);

            item = new QStandardItem(employeesList.at(row)->getName());
            m_employeeModel->setItem(row,2,item);

            item = new QStandardItem(employeesList.at(row)->getUsername());
            m_employeeModel->setItem(row,3,item);

            item = new QStandardItem(Employee::getRoleString(
                                         employeesList.at(row)->getRole()));
            m_employeeModel->setItem(row,4,item);
        }
    }
    else
    {
        showStatusMessage(tr("Search Employee: no employees found!"));
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

    QColor usedColor;

    m_activityModel->clear();
    m_activityModel->setColumnCount(7);
//    m_activityModel->sort(1,Qt::AscendingOrder);

    m_activityModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_activityModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    m_activityModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Work Order"));
    m_activityModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Employee"));
    m_activityModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Priority"));
    m_activityModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Status"));
    m_activityModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Type"));

    QVector<Activity*> activitiesList =
            m_activityController->getActivitiesList(searchParams);

    qDebug() << "MainWindow::updateActivitiesTable() - Activities size:" << activitiesList.size();
    if (activitiesList.size()>0)
    {
        /* Get the employees list */
        QStringList employeesSearchParams;
        employeesSearchParams << "Active=Yes";
        QVector<Employee*> employeesList =
                m_employeeController->getEmployeesList(employeesSearchParams);
        qDebug() << "MainWindow::updateActivitiesTable() - Employees size:" << employeesList.size();

        for (int row = 0; row < activitiesList.size(); ++row)
        {
            qDebug() << "MainWindow::updateActivitiesTable() - db deadline" << activitiesList.at(row)->getDeadline();
            QDate deadline = activitiesList.at(row)->getDeadline();

            if (activitiesList.at(row)->getStatus() == Activity::Ended)
            {
                qDebug() << "MainWindow::updateActivitiesTable() - Ended!";
                usedColor = m_colorEnded;
            }
            else if (deadline < shortDeadline)
            {
//                isShortDeadline = true;
                usedColor = m_colorDanger;
                qDebug() << "MainWindow::updateActivitiesTable() - less than 7 days!";
            }
            else if (deadline < mediumDeadline)
            {
//                isMediumDeadline = true;
                usedColor = m_colorWarning;
                qDebug() << "MainWindow::updateActivitiesTable() - less then 21 days!";
            }
            else
            {
                usedColor = m_colorNoProblem;
            }

            QStandardItem *item;

            /* ID */
            item = new QStandardItem(QString::number(activitiesList.at(row)->getId()));
            m_activityModel->setItem(row,0,item);
            item->setBackground(QBrush(usedColor));

            /* Title */
            item = new QStandardItem((activitiesList.at(row))->getTitle());
            m_activityModel->setItem(row,1,item);
            item->setBackground(QBrush(usedColor));

            /* Work Order */
            item = new QStandardItem((activitiesList.at(row))->getWorkCode());
            m_activityModel->setItem(row,2,item);
            item->setBackground(QBrush(usedColor));

            uint employeeId = activitiesList.at(row)->getEmployee();
            for (int i = 0; i < employeesList.size(); ++i)
            {
                uint searchEmployeeId = (employeesList.at(i))->getId();
                if (employeeId == searchEmployeeId)
                {
                    item = new QStandardItem(
                        employeesList.at(i)->getSurname() + " " + employeesList.at(i)->getName()
                    );
                    break;
                }
            }
            m_activityModel->setItem(row,3,item);
            item->setBackground(QBrush(usedColor));

            /* Priority */
            item = new QStandardItem(Activity::getPriorityString(
                                         (activitiesList.at(row))->getPriority()));
            m_activityModel->setItem(row,4,item);
            item->setBackground(QBrush(usedColor));

            /* Status */
            item = new QStandardItem(Activity::getStatusString(
                                         (activitiesList.at(row))->getStatus()));
            m_activityModel->setItem(row,5,item);
            item->setBackground(QBrush(usedColor));

            /* Type */
            item = new QStandardItem(Activity::getTypeString(
                                         (activitiesList.at(row))->getType()));
            m_activityModel->setItem(row,6,item);
            item->setBackground(QBrush(usedColor));

            isMediumDeadline = false;
            isShortDeadline = false;
        }
    }
    else
    {
        showStatusMessage(tr("Search Activity: no activities found!"));
    }
}

void MainWindow::searchActivities()
{
    qDebug() << "MainWindow::searchActivities()";
    QStringList searchParams;

    if (!ui->searchActivityText->text().isEmpty())
    {
        QString text = "Text%" + ui->searchActivityText->text();
        qDebug() << "MainWindow::searchActivities() - String" << text;
        searchParams << text;
    }

    if (ui->searchActivityPriorityCombobox->currentData().toInt() != -1)
    {
        QString priority = "Priority=";
        priority.append(Activity::getPriorityString(
            static_cast<Activity::Priority>(ui->searchActivityPriorityCombobox->currentData().toInt()))
        );
        qDebug() << "MainWindow::searchActivities() - Priority" << priority ;
        searchParams << priority;
    }

    if (ui->searchActivityTypeCombobox->currentData().toInt() != -1)
    {
        QString type = "Type=";
        type.append(Activity::getTypeString(
            static_cast<Activity::Type>(ui->searchActivityTypeCombobox->currentData().toInt()))
        );
        qDebug() << "MainWindow::searchActivities() - Type" << type ;
        searchParams << type;
    }

    if (ui->searchActivityEmployeeCombobox->currentData().toInt() > 0)
    {
        QString employee = "Employee=";
        employee.append(QString::number(ui->searchActivityEmployeeCombobox->currentData().toInt()));
        qDebug() << "MainWindow::searchActivities() - Employee" << employee ;
        searchParams << employee;
    }

    if (ui->searchActivityStatusCombobox->currentData().toInt() > -1)
    {
        QString status = "Status=";
        status.append(Activity::getStatusString(
            static_cast<Activity::Status>(ui->searchActivityStatusCombobox->currentData().toInt()))
        );
        qDebug() << "MainWindow::searchActivities() - Status" << status ;
        searchParams << status;
    }
    else if (ui->searchActivityStatusCombobox->currentData().toInt() == -2)
    {
        qDebug() << "MainWindow::searchActivities() - Status" << "Status$NotStarted|InProgress|Waiting" ;
        searchParams << "Status$NotStarted|InProgress|Waiting";
    }

    qDebug() << "MainWindow::searchActivities() - update table";
    updateActivitiesTable(searchParams);
}

void MainWindow::resetSearchActivities()
{
    qDebug() << "MainWindow::resetSearchActivities()";
    QStringList searchParams;
    searchParams << "Status$NotStarted|InProgress|Waiting";

    ui->searchActivityText->setText("");
    ui->searchActivityStatusCombobox->setCurrentIndex(0);
    ui->searchActivityEmployeeCombobox->setCurrentIndex(0);
    ui->searchActivityTypeCombobox->setCurrentIndex(0);
    ui->searchActivityPriorityCombobox->setCurrentIndex(0);

    qDebug() << "MainWindow::resetSearchActivities() - update table";
    updateActivitiesTable(searchParams);
}

void MainWindow::selectionChangedProductionsTable(const QItemSelection & sel,
                                                  const QItemSelection & des)
{
    qDebug() << "MainWindow::selectionChangedProductionsTable()";
    QModelIndexList indexes = sel.indexes();
    qDebug() << "MainWindow::selectionChangedProductionsTable() - selected number" << indexes.count();

    qDebug() << "MainWindow::selectionChangedProductionsTable() - row selected" << indexes.at(0).row();
    m_productionSelected = m_productionModel->item(indexes.at(0).row(),0)->text().toInt();
}

void MainWindow::updateProductionsTable(QStringList searchParams)
{
    qDebug() << "MainWindow::updateProductionsTable()";

    m_productionModel->clear();
    m_productionModel->setColumnCount(7);
//    m_productionModel->sort(1,Qt::AscendingOrder);

    m_productionModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    m_productionModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    m_productionModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Work Order"));
    m_productionModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Output Code"));
    m_productionModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Employee"));
    m_productionModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Status"));
    m_productionModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Supplier"));

    QVector<Production*> productionsList =
            m_productionController->getProductionsList(searchParams);

    qDebug() << "MainWindow::updateProductionsTable() - Productions size:" << productionsList.size();
    if (productionsList.size()>0)
    {
        /* Get the employees list */
        QStringList employeesSearchParams;
        employeesSearchParams << "Active=Yes";
        QVector<Employee*> employeesList =
                m_employeeController->getEmployeesList(employeesSearchParams);
        qDebug() << "MainWindow::productionsList() - Employees size:" << employeesList.size();


        for (int row = 0; row < productionsList.size(); ++row)
        {
            QStandardItem *item;

            /* ID */
            item = new QStandardItem(QString::number(productionsList.at(row)->getId()));
            m_productionModel->setItem(row,0,item);

            /* Title */
            item = new QStandardItem((productionsList.at(row))->getTitle());
            m_productionModel->setItem(row,1,item);

            /* Work Order */
            item = new QStandardItem((productionsList.at(row))->getWorkCode());
            m_productionModel->setItem(row,2,item);

            /* Output Code */
            item = new QStandardItem((productionsList.at(row))->getOutputCode());
            m_productionModel->setItem(row,3,item);

            uint employeeId = (productionsList.at(row))->getEmployee();
            for (int i = 0; i < employeesList.size(); ++i)
            {
                uint searchEmployeeId = (employeesList.at(i))->getId();
                if (employeeId == searchEmployeeId)
                {
                    item = new QStandardItem(
                        employeesList.at(i)->getSurname() + " " + employeesList.at(i)->getName()
                    );
                    break;
                }
            }
            m_productionModel->setItem(row,4,item);

            /* Status */
            item = new QStandardItem(Production::getStatusString(
                                         (productionsList.at(row))->getStatus()));
            m_productionModel->setItem(row,5,item);

            /* TODO: Supplier */
            item = new QStandardItem("-");
            m_productionModel->setItem(row,6,item);
        }
    }
    else
    {
        showStatusMessage(tr("Search Production: no items found!"));
    }
}

void MainWindow::searchProductions()
{
    qDebug() << "MainWindow::searchProductions()";
    QStringList searchParams;

    if (!ui->searchProductionText->text().isEmpty())
    {
        QString text = "Text%" + ui->searchProductionText->text();
        qDebug() << "MainWindow::searchProductions() - String" << text;
        searchParams << text;
    }

/* TODO!!! */
//    if (ui->searchProductionSupplierCombobox->currentData().toInt() != -1)
//    {
//        QString supplier = "Supplier=";

//        qDebug() << "MainWindow::searchProductions() - Supplier" << supplier ;
//        searchParams << supplier;
//    }

    if (ui->searchProductionEmployeeCombobox->currentData().toInt() > 0)
    {
        QString employee = "Employee=";
        employee.append(QString::number(ui->searchProductionEmployeeCombobox->currentData().toInt()));
        qDebug() << "MainWindow::searchProductions() - Employee" << employee ;
        searchParams << employee;
    }

    if (ui->searchProductionStatusCombobox->currentData().toInt() > -1)
    {
        QString status = "Status=";
        status.append(Production::getStatusString(
            static_cast<Production::Status>(ui->searchProductionStatusCombobox->currentData().toInt()))
        );
        qDebug() << "MainWindow::searchProductions() - Status" << status ;
        searchParams << status;
    }
    else if (ui->searchProductionStatusCombobox->currentData().toInt() == -2)
    {
        qDebug() << "MainWindow::searchProductions() - Status" << "Status$NotStarted|InProgress|Waiting" ;
        searchParams << "Status$NotStarted|InProgress|Waiting";
    }

    qDebug() << "MainWindow::searchProductions() - update table";
    updateProductionsTable(searchParams);
}

void MainWindow::resetSearchProductions()
{
    qDebug() << "MainWindow::resetSearchProductions()";
    QStringList searchParams;
    searchParams << "Status$NotStarted|InProgress|Waiting";

    ui->searchProductionText->setText("");
    ui->searchProductionStatusCombobox->setCurrentIndex(0);
    ui->searchProductionEmployeeCombobox->setCurrentIndex(0);
    ui->searchProductionSupplierCombobox->setCurrentIndex(0);

    qDebug() << "MainWindow::resetSearchProductions() - update table";
    updateProductionsTable(searchParams);
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

    m_employeeLogged = 0;
    ui->loginLabel->setText(tr("Welcome unknown User!"));

    disconnect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogout()));
    ui->loginButton->setText(tr("Login"));
    connect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogin()));

    updateButtonStatus();

    emit changedLoggedUser();

    qDebug() << "MainWindow::userLogout() - Exit!";
}

void MainWindow::loggedUser(Employee *employee)
{
    qDebug() << "MainWindow::loggedUser()";

    m_employeeLogged = employee;

    ui->loginLabel->setText(
        tr("Welcome ") + employee->getName() + " " + employee->getSurname() + "!");

    disconnect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogin()));
    ui->loginButton->setText(tr("Logout"));
    connect(ui->loginButton,SIGNAL(clicked()),
            this,SLOT(userLogout()));

    updateButtonStatus();

    emit changedLoggedUser();

    qDebug() << "MainWindow::loggedUser() - Exit!";
}

void MainWindow::updateButtonStatus()
{
    qDebug() << "MainWindow::updateButtonStatus()";
    if (m_employeeLogged == 0)
    {
        qDebug() << "MainWindow::updateButtonStatus() - No logged!";

        /* Activity tab buttons */
        disconnect(ui->addActivityButton,SIGNAL(clicked()),
                this,SLOT(openActivityDialog()));
        ui->addActivityButton->setEnabled(false);

        ui->viewActivityButton->setEnabled(true);

        disconnect(ui->editActivityButton,SIGNAL(clicked()),
                this,SLOT(openActivityDialog()));
        ui->editActivityButton->setEnabled(false);

        disconnect(ui->deleteActivityButton,SIGNAL(clicked()),
                this,SLOT(openActivityDialog()));
        ui->deleteActivityButton->setEnabled(false);

        disconnect(ui->addNoteActivityButton,SIGNAL(clicked()),
                this,SLOT(openActivityDialog()));
        ui->addNoteActivityButton->setEnabled(false);

        /* Production tab buttons */
        disconnect(ui->addProductionButton,SIGNAL(clicked()),
                this,SLOT(openProductionDialog()));
        ui->addProductionButton->setEnabled(false);

        ui->viewProductionButton->setEnabled(true);

        disconnect(ui->editProductionButton,SIGNAL(clicked()),
                this,SLOT(openProductionDialog()));
        ui->editProductionButton->setEnabled(false);

        disconnect(ui->deleteProductionButton,SIGNAL(clicked()),
                this,SLOT(openProductionDialog()));
        ui->deleteProductionButton->setEnabled(false);

        disconnect(ui->addNoteProductionButton,SIGNAL(clicked()),
                this,SLOT(openProductionDialog()));
        ui->addNoteProductionButton->setEnabled(false);

        /* Employee tab buttons */
        disconnect(ui->addEmployeeButton,SIGNAL(clicked()),
                this,SLOT(openEmployeeDialog()));
        ui->addEmployeeButton->setEnabled(false);

        ui->viewEmployeeButton->setEnabled(true);

        disconnect(ui->editEmployeeButton,SIGNAL(clicked()),
                this,SLOT(openEmployeeDialog()));
        ui->editEmployeeButton->setEnabled(false);
    }
    else
    {
        qDebug() << "MainWindow::updateButtonStatus() - Logged!";
        connect(ui->addActivityButton,SIGNAL(clicked()),
                this,SLOT(openActivityDialog()));
        ui->addActivityButton->setEnabled(true);

        ui->viewActivityButton->setEnabled(true);

        connect(ui->editActivityButton,SIGNAL(clicked()),
                this,SLOT(openActivityDialog()));
        ui->editActivityButton->setEnabled(true);

        connect(ui->addNoteActivityButton,SIGNAL(clicked()),
                this,SLOT(openActivityDialog()));
        ui->addNoteActivityButton->setEnabled(true);

        /* Production tab buttons */
        connect(ui->addProductionButton,SIGNAL(clicked()),
                this,SLOT(openProductionDialog()));
        ui->addProductionButton->setEnabled(true);

        ui->viewProductionButton->setEnabled(true);

        connect(ui->editProductionButton,SIGNAL(clicked()),
                this,SLOT(openProductionDialog()));
        ui->editProductionButton->setEnabled(true);

        disconnect(ui->deleteProductionButton,SIGNAL(clicked()),
                this,SLOT(openProductionDialog()));
        ui->deleteProductionButton->setEnabled(false);

        connect(ui->addNoteProductionButton,SIGNAL(clicked()),
                this,SLOT(openProductionDialog()));
        ui->addNoteProductionButton->setEnabled(true);

        switch (m_employeeLogged->getSystemRole())
        {
        case Employee::Editor:
            qDebug() << "MainWindow::updateButtonStatus() - Logged Editor!";
            disconnect(ui->addEmployeeButton,SIGNAL(clicked()),
                    this,SLOT(openEmployeeDialog()));
            ui->addEmployeeButton->setEnabled(false);

            ui->viewEmployeeButton->setEnabled(true);

            disconnect(ui->editEmployeeButton,SIGNAL(clicked()),
                    this,SLOT(openEmployeeDialog()));
            ui->editEmployeeButton->setEnabled(false);

            disconnect(ui->deleteActivityButton,SIGNAL(clicked()),
                    this,SLOT(openActivityDialog()));
            ui->deleteActivityButton->setEnabled(false);

            disconnect(ui->deleteProductionButton,SIGNAL(clicked()),
                    this,SLOT(openProductionDialog()));
            ui->deleteProductionButton->setEnabled(false);

            break;

        case Employee::Administrator:
            qDebug() << "MainWindow::updateButtonStatus() - Logged Admin!";
            connect(ui->addEmployeeButton,SIGNAL(clicked()),
                    this,SLOT(openEmployeeDialog()));
            ui->addEmployeeButton->setEnabled(true);

            ui->viewEmployeeButton->setEnabled(true);

            connect(ui->editEmployeeButton,SIGNAL(clicked()),
                    this,SLOT(openEmployeeDialog()));
            ui->editEmployeeButton->setEnabled(true);

            connect(ui->deleteActivityButton,SIGNAL(clicked()),
                    this,SLOT(openActivityDialog()));
            ui->deleteActivityButton->setEnabled(true);

            connect(ui->deleteProductionButton,SIGNAL(clicked()),
                    this,SLOT(openProductionDialog()));
            ui->deleteProductionButton->setEnabled(true);

            break;
        default:
            /* Nothing to do! */
            break;
        }
    }
    qDebug() << "MainWindow::updateButtonStatus() - Exit!";
}

void MainWindow::updateLoggedUser ()
{
    m_activityController->updateLoggedUser(m_employeeLogged);
    m_productionController->updateLoggedUser(m_employeeLogged);
    m_employeeController->updateLoggedUser(m_employeeLogged);
}

void MainWindow::showStatusMessage(QString message)
{
    qDebug() << "STATUS MESSAGE:" << message;
    ui->statusBar->showMessage(message);
}

void MainWindow::managePreferences()
{
    qDebug() << "MainWindow::managePreferences()";
    m_preferencesDialog->exec();
    qDebug() << "MainWindow::managePreferences() - Exit!";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MainWindow::closeEvent()";
//    if (userReallyWantsToQuit()) {
//        writeSettings();
//        event->accept();
//    } else {
//        event->ignore();
//    }
}

void MainWindow::switchTranslator(QTranslator& translator, const QString& filename)
{
    // remove the old translator
    qApp->removeTranslator(&translator);

    // load the new translator
    if(translator.load(filename))
        qApp->installTranslator(&translator);
}

void MainWindow::loadLanguage(const QString& language)
{
    qDebug() << "MainWindow::loadLanguage()";
    if(m_currentLanguage != language)
    {
        m_currentLanguage = language;
        QLocale locale = QLocale(m_currentLanguage);
        QLocale::setDefault(locale);
        QString languageName = QLocale::languageToString(locale.language());
        switchTranslator(m_translator, QString("%1/LabOrTool_%2.qm").arg(m_langPath).arg(language));
        switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(language));
        showStatusMessage(tr("Current Language changed to %1").arg(languageName));
    }
}

void MainWindow::languageChanged(QAction* action)
{
    if(0 != action)
    {
        // load the language dependant on the action content
        loadLanguage(action->data().toString());
    }
}

void MainWindow::createLanguageMenu()
{
    qDebug() << "MainWindow::createLanguageMenu()";
    QActionGroup* langGroup = new QActionGroup(ui->menuLanguage);
    langGroup->setExclusive(true);

    connect(langGroup, SIGNAL (triggered(QAction *)),
            this, SLOT (languageChanged(QAction *)));

    // format systems language
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"

    m_langPath = QApplication::applicationDirPath();
    m_langPath.append("/languages");
    qDebug() << "MainWindow::createLanguageMenu() - Dir" << m_langPath ;
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList("LabOrTool_*.qm"));
    qDebug() << "MainWindow::createLanguageMenu() - Files" << fileNames ;

    for (int i = 0; i < fileNames.size(); ++i)
    {
        // get locale extracted by filename
        QString locale;
        locale = fileNames[i]; // "LabOrTool_de.qm"
        locale.truncate(locale.lastIndexOf('.')); // "LabOrTool_de"
        locale.remove(0, locale.indexOf('_') + 1); // "de"

        QString lang = QLocale::languageToString(QLocale(locale).language());
        QIcon ico(QString(":language/%1").arg(locale));

        QAction *action = new QAction(ico, lang, this);
        action->setCheckable(true);
        action->setData(locale);

        ui->menuLanguage->addAction(action);
        langGroup->addAction(action);

        // set default translators and language checked
        if (defaultLocale == locale)
        {
            action->setChecked(true);
            loadLanguage(locale);
        }
    }
}

void MainWindow::changeEvent(QEvent* event)
{
    qDebug() << "MainWindow::changeEvent()";
    if(0 != event)
    {
        switch(event->type())
        {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;

        // this event is send, if the system, language changes
        case QEvent::LocaleChange:
            {
            QString locale = QLocale::system().name();
            locale.truncate(locale.lastIndexOf('_'));
            loadLanguage(locale);
            }
            break;

        default:
            break;
        }
    }
    QMainWindow::changeEvent(event);
}
