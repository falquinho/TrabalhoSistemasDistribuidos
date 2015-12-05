#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T18:59:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SD_Trab2_Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lspread -ldl -lm -lrt -lnsl

SOURCES += main.cpp \
    communicationmanager.cpp \
    errorlog.cpp \
    servercommunicator.cpp \
    directory.cpp \
    electionsystem.cpp

HEADERS += \
    communicationmanager.h \
    errorlog.h \
    servercommunicator.h \
    directory.h \
    electionsystem.h
