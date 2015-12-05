#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T17:45:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SD_Trab3_Slave
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lspread -ldl -lm -lrt -lnsl

SOURCES += main.cpp \
    communicationmanager.cpp \
    wordextractor.cpp \
    filemanager.cpp \
    errorlog.cpp \
    slavecommunicator.cpp

HEADERS += \
    communicationmanager.h \
    wordextractor.h \
    filemanager.h \
    errorlog.h \
    slavecommunicator.h
