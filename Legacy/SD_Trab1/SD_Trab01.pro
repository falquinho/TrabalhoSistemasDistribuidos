TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lspread -ldl -lm -lrt -lnsl

SOURCES += main.cpp \
    serverbank.cpp \
    serverinfo.cpp \
    communicator.cpp \
    errorhandling.cpp \
    utils.cpp

HEADERS += \
    serverbank.h \
    serverinfo.h \
    communicator.h \
    utils.h \
    errorhandling.h \
    usefuldefines.h

