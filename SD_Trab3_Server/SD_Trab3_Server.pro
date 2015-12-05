#-------------------------------------------------
#
# Project created by QtCreator 2015-11-05T16:32:49
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SD_Trab3_Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lspread -ldl -lm -lrt -lnsl

SOURCES += main.cpp \
    resourcemanager.cpp \
    slavesmanager.cpp \
    servermanager.cpp \
    communicationmanager.cpp \
    errorlog.cpp

HEADERS += \
    resourcemanager.h \
    slavesmanager.h \
    servermanager.h \
    communicationmanager.h \
    errorlog.h
