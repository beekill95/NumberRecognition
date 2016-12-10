TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    snndata.cpp \
    snnlayer.cpp \
    snn.cpp

HEADERS += \
    snndata.h \
    snnlayer.h \
    snnfunction.h \
    snn.h

debug {
    DEFINES += VERBOSE
}

DISTFILES += \
    SimpleNeuralNetwork.pri
