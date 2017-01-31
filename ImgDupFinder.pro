#-------------------------------------------------
#
# Project created by QtCreator 2014-08-14T13:10:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgDupFinder
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Utils.cpp \
    ImageHashInfo.cpp \
    Hashes.cpp

HEADERS  += MainWindow.h \
    Utils.h \
    ImageHashInfo.h \
    Hashes.h

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
