TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += ../NumberRecognition ../SimpleNeuralNetwork ../SimpleNeuralNetwork/cereal
SOURCES += main.cpp
LIBS += -L../NumberRecognition -lNumberRecognition -L../SimpleNeuralNetwork -lSimpleNeuralNetwork -lopencv_core -lopencv_imgproc -lopencv_highgui

