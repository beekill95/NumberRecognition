TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
LIBS += -lopencv_core -lopencv_highgui

SOURCES += main.cpp \
    mnistloader/mnistloader.cpp

HEADERS += \
    mnistloader/mnistloader.h

