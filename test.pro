#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T22:33:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app
CONFIG += C++11
QMAKE_CXXFLAGS += /wd4996
SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    config.cpp \
    login.cpp \
    regist.cpp \
    index.cpp \
    booker.cpp \
    admin.cpp \
    user.cpp \
    bookmanager.cpp \
    myuser.cpp \
    usermanager.cpp \
    bookimformation.cpp

HEADERS  += mainwindow.h \
    data.h \
    config.h \
    login.h \
    regist.h \
    index.h \
    bookmanager.h \
    booker.h \
    admin.h \
    user.h \
    myuser.h \
    usermanager.h \
    bookimformation.h

FORMS    += mainwindow.ui \
    login.ui \
    regist.ui \
    index.ui \
    bookmanager.ui \
    admin.ui \
    user.ui \
    usermanager.ui \
    bookimformation.ui

RESOURCES += \
    qrc.qrc
