#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T15:48:59
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatServer
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    server.cpp \
    client.cpp

HEADERS  += \
    mainwindow.h \
    server.h \
    client.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
