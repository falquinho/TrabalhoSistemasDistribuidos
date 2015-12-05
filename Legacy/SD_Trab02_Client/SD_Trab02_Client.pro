#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T21:09:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SD_Trab02_Client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lm -lrt -lnsl -lspread

SOURCES += main.cpp \
    userinterface.cpp \
    communicationmanager.cpp \
    clientcommunicator.cpp \
    errorlog.cpp

HEADERS += \
    userinterface.hpp \
    communicationmanager.h \
    clientcommunicator.h \
    errorlog.h
