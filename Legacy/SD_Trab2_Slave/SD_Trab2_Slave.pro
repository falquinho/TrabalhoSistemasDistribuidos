TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += core
QT -= gui

LIBS += -lspread -ldl -lm -lrt -lnsl

SOURCES += main.cpp \
    fsemulator.cpp \
    communicationmanager.cpp \
    errorlog.cpp \
    slavecommunicator.cpp

HEADERS += \
    fsemulator.h \
    errorlog.h \
    communicationmanager.h \
    slavecommunicator.h

