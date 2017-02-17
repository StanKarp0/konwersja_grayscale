#-------------------------------------------------
#
# Project created by QtCreator 2016-12-23T17:13:36
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjektKonwersja
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    abstractconversion.cpp \
    conversions.cpp \
    conffile.cpp \
    conversiontool.cpp

HEADERS  += mainwindow.h \
    abstractconversion.h \
    conversions.h \
    conffile.h \
    conversiontool.h

FORMS    += mainwindow.ui
