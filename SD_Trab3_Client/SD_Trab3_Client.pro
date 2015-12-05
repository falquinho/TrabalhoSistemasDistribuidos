#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T06:56:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SD_Trab3_Client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lspread -ldl -lm -lrt -lnsl

SOURCES += main.cpp \
    userinterface.cpp \
    communicationmanager.cpp \
    clientmanager.cpp \
    errorlog.cpp \
    wordextractor.cpp

HEADERS += \
    userinterface.h \
    communicationmanager.h \
    clientmanager.h \
    errorlog.h \
    wordextractor.h
