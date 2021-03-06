#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T19:38:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComputerLog
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainpage.cpp \
    src/eventlog.cpp \
    src/managelog.cpp \
    tools/linkedlist.cpp \
    tools/tool.cpp \
    adddialog.cpp \
    src/managegraph.cpp \
    src/eventgraph.cpp \
    tools/gnode.cpp

HEADERS += \
        mainpage.h \
    src/eventlog.h \
    src/managelog.h \
    tools/linkedlist.h \
    tools/tool.h \
    adddialog.h \
    src/managegraph.h \
    src/eventgraph.h \
    tools/gnode.h

FORMS += \
        mainpage.ui \
    adddialog.ui

DISTFILES += \
    resource/icons/Analysis1.png \
    resource/icons/Event1.png \
    resource/icons/Graph1.png

RESOURCES += \
    res.qrc
