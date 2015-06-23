#-------------------------------------------------
#
# Project created by QtCreator 2014-07-07T13:37:30
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LabOrTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    employee.cpp \
    activity.cpp \
    activitydatabase.cpp \
    activitycontroller.cpp \
    activitydialog.cpp \
    employeecontroller.cpp \
    employeedialog.cpp \
    employeedatabase.cpp \
    logindialog.cpp \
    logincontroller.cpp \
    preferencesdialog.cpp \
    preferences.cpp \
    production.cpp \
    productiondatabase.cpp \
    note.cpp \
    productioncontroller.cpp \
    productiondialog.cpp \
    notedatabase.cpp \
    notedialog.cpp

HEADERS  += mainwindow.h \
    metadata.h \
    employee.h \
    activity.h \
    activitydatabase.h \
    activitycontroller.h \
    activitydialog.h \
    employeecontroller.h \
    employeedialog.h \
    employeedatabase.h \
    logindialog.h \
    logincontroller.h \
    preferencesdialog.h \
    preferences.h \
    production.h \
    productiondatabase.h \
    note.h \
    productioncontroller.h \
    productiondialog.h \
    notedatabase.h \
    notedialog.h

FORMS    += mainwindow.ui \
    activitydialog.ui \
    employeedialog.ui \
    logindialog.ui \
    notedialog.ui \
    preferencesdialog.ui \
    productiondialog.ui

OTHER_FILES += \
    ChangeLog \
    LICENSE \
    TODO \
    README \
    labortool.sql \
    VersionLog
