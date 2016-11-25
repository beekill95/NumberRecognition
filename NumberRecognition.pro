TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
LIBS += -lopencv_core -lopencv_highgui

SOURCES += main.cpp \
    mnistloader/mnistloader.cpp \
    featureextraction/featuresetextractor.cpp \
    recognizer/knearestneighbors.cpp \
    featureextraction/pixelfeature/pixelextractor.cpp

HEADERS += \
    mnistloader/mnistloader.h \
    featureextraction/featureextractor.h \
    featureextraction/featuresetextractor.h \
    recognizer/recognizer.h \
    recognizer/knearestneighbors.h \
    featureextraction/pixelfeature/pixelextractor.h

