#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T15:52:06
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClient
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mysocket.cpp \
    dialog.cpp

HEADERS  += \
    mainwindow.h \
    mysocket.h \
    dialog.h

FORMS    += \
    mainwindow.ui \
    dialog.ui

RESOURCES += \
    images.qrc
