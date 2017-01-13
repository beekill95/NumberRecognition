TEMPLATE = lib
CONFIG += staticlib c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
LIBS += -L../SimpleNeuralNetwork -lSimpleNeuralNetwork -lopencv_core -lopencv_imgproc -lopencv_highgui -lgtest -lpthread

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CFLAGS_RELEASE *= -march=native
#QMAKE_CXXFLAGS_RELEASE *= -march=native
QMAKE_CXXFLAGS_RELEASE *= -O3

INCLUDEPATH += ../SimpleNeuralNetwork ../SimpleNeuralNetwork/cereal

SOURCES += mnistloader/mnistloader.cpp \
    featureextraction/featuresetextractor.cpp \
    recognizer/knearestneighbors.cpp \
    featureextraction/pixelfeature/pixelextractor.cpp \
    featureextraction/statisticalfeatures/histogram/meanhistogram.cpp \
    featureextraction/statisticalfeatures/histogram/histogrambaseddescriptor.cpp \
    featureextraction/statisticalfeatures/histogram/moment.cpp \
    featureextraction/statisticalfeatures/histogram/relativesmoothness.cpp \
    featureextraction/statisticalfeatures/histogram/uniformity.cpp \
    featureextraction/statisticalfeatures/histogram/averageentropy.cpp \
    featureextraction/statisticalfeatures/cooccurencematrix/cooccurrencematrixbaseddescriptor.cpp \
    featureextraction/statisticalfeatures/cooccurencematrix/maximumprobability.cpp \
    featureextraction/statisticalfeatures/cooccurencematrix/correlation.cpp \
    featureextraction/statisticalfeatures/cooccurencematrix/contrast.cpp \
    featureextraction/statisticalfeatures/cooccurencematrix/homogeneity.cpp \
    featureextraction/statisticalfeatures/cooccurencematrix/entropy.cpp \
    featureextraction/statisticalfeatures/cooccurencematrix/uniformitycooccurence.cpp \
    validator/validator.cpp \
    recognizer/neuralnetwork.cpp \
    preprocessing/preprocessingimage.cpp \
    featureextraction/boundaryfeature/boundaryfeature.cpp \
    common.cpp

HEADERS += \
    mnistloader/mnistloader.h \
    featureextraction/featureextractor.h \
    featureextraction/featuresetextractor.h \
    recognizer/recognizer.h \
    recognizer/knearestneighbors.h \
    featureextraction/pixelfeature/pixelextractor.h \
    featureextraction/statisticalfeatures/histogram/meanhistogram.h \
    featureextraction/statisticalfeatures/histogram/histogrambaseddescriptor.h \
    featureextraction/statisticalfeatures/histogram/moment.h \
    featureextraction/statisticalfeatures/histogram/relativesmoothness.h \
    featureextraction/statisticalfeatures/histogram/uniformity.h \
    featureextraction/statisticalfeatures/histogram/averageentropy.h \
    featureextraction/statisticalfeatures/cooccurencematrix/cooccurrencematrixbaseddescriptor.h \
    featureextraction/statisticalfeatures/cooccurencematrix/maximumprobability.h \
    featureextraction/statisticalfeatures/cooccurencematrix/correlation.h \
    featureextraction/statisticalfeatures/cooccurencematrix/contrast.h \
    featureextraction/statisticalfeatures/cooccurencematrix/homogeneity.h \
    featureextraction/statisticalfeatures/cooccurencematrix/entropy.h \
    featureextraction/statisticalfeatures/cooccurencematrix/uniformitycooccurence.h \
    validator/validator.h \
    featureextraction/pixelfeature/pixelfeature.h \
    featureextraction/statisticalfeatures/cooccurencematrix/cooccurencematrixfeature.h \
    featureextraction/statisticalfeatures/histogram/histogramfeature.h \
    featureextraction/statisticalfeatures/statisticalfeature.h \
    recognizer/neuralnetwork.h \
    definition.h \
    preprocessing/preprocessingimage.h \
    featureextraction/boundaryfeature/boundaryfeature.h \
    common.h

CONFIG(debug, debug|release) {
    DEFINES += VERBOSE TIME_PROFILING
}

CONFIG(release, debug|release) {
    DEFINES += VERBOSE TIME_PROFILING
}
