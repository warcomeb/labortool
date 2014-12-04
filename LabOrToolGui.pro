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
    activitynote.cpp \
    activitydatabase.cpp \
    activitycontroller.cpp \
    activitydialog.cpp \
    employeecontroller.cpp \
    employeedialog.cpp \
    employeedatabase.cpp \
    logindialog.cpp \
    logincontroller.cpp \
    activitynotedialog.cpp

HEADERS  += mainwindow.h \
    metadata.h \
    employee.h \
    activity.h \
    activitynote.h \
    activitydatabase.h \
    activitycontroller.h \
    activitydialog.h \
    employeecontroller.h \
    employeedialog.h \
    employeedatabase.h \
    logindialog.h \
    logincontroller.h \
    activitynotedialog.h

FORMS    += mainwindow.ui \
    activitydialog.ui \
    employeedialog.ui \
    logindialog.ui \
    activitynotedialog.ui

OTHER_FILES += \
    ChangeLog \
    LICENSE \
    TODO \
    README \
    labortool.sql \
    VersionLog
