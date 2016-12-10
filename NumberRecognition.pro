TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(recognizer/SimpleNeuralNetwork/SimpleNeuralNetwork.pro)

QMAKE_CXXFLAGS += -std=c++11
LIBS += -lopencv_core -lopencv_highgui -lgtest -lpthread

SOURCES += main.cpp \
    mnistloader/mnistloader.cpp \
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
    tests/meanhistogramtest.cpp \
    featureextraction/statisticalfeatures/cooccurencematrix/uniformitycooccurence.cpp \
    tests/maxprobabilitytest.cpp \
    tests/contrasttest.cpp \
    tests/pixelextractortest.cpp \
    validator/validator.cpp \
    tests/correlationtest.cpp \
    tests/testuniformitycooccurrence.cpp \
    tests/homogeneitytest.cpp \
    tests/cooccurrenceentropytest.cpp \
    tests/smoothnesstest.cpp \
    tests/momenttest.cpp \
    tests/uniformityhistogramtest.cpp \
    tests/entropyhistogramtest.cpp

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
    tests/common.h \
    validator/validator.h \
    featureextraction/pixelfeature/pixelfeature.h \
    featureextraction/statisticalfeatures/cooccurencematrix/cooccurencematrixfeature.h \
    featureextraction/statisticalfeatures/histogram/histogramfeature.h \
    featureextraction/statisticalfeatures/statisticalfeature.h

debug {
    DEFINES += GTEST
}
