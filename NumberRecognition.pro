TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEPENDPATH += . recognizer/SimpleNeuralNetwork
INCLUDEPATH += . recognizer/SimpleNeuralNetwork
include(recognizer/SimpleNeuralNetwork/SimpleNeuralNetwork.pri)

QMAKE_CXXFLAGS += -std=c++11
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lgtest -lpthread

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CFLAGS_RELEASE *= -march=native
#QMAKE_CXXFLAGS_RELEASE *= -march=native
QMAKE_CXXFLAGS_RELEASE *= -O3

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
    tests/entropyhistogramtest.cpp \
    recognizer/neuralnetwork.cpp \
    preprocessing/preprocessingimage.cpp \
    featureextraction/boundaryfeature/boundaryfeature.cpp \
#    recognizer/SimpleNeuralNetwork/main.cpp \
#    recognizer/SimpleNeuralNetwork/snn.cpp \
#    recognizer/SimpleNeuralNetwork/snndata.cpp \
#    recognizer/SimpleNeuralNetwork/snnlayer.cpp

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
    featureextraction/statisticalfeatures/statisticalfeature.h \
    recognizer/neuralnetwork.h \
    definition.h \
    preprocessing/preprocessingimage.h \
    featureextraction/boundaryfeature/boundaryfeature.h \
#    recognizer/SimpleNeuralNetwork/snn.h \
#    recognizer/SimpleNeuralNetwork/snndata.h \
#    recognizer/SimpleNeuralNetwork/snnfunction.h \
#    recognizer/SimpleNeuralNetwork/snnlayer.h \
    recognizer/SimpleNeuralNetwork/cereal/archives/adapters.hpp \
    recognizer/SimpleNeuralNetwork/cereal/archives/binary.hpp \
    recognizer/SimpleNeuralNetwork/cereal/archives/json.hpp \
    recognizer/SimpleNeuralNetwork/cereal/archives/portable_binary.hpp \
    recognizer/SimpleNeuralNetwork/cereal/archives/xml.hpp \
    recognizer/SimpleNeuralNetwork/cereal/details/helpers.hpp \
    recognizer/SimpleNeuralNetwork/cereal/details/polymorphic_impl.hpp \
    recognizer/SimpleNeuralNetwork/cereal/details/polymorphic_impl_fwd.hpp \
    recognizer/SimpleNeuralNetwork/cereal/details/static_object.hpp \
    recognizer/SimpleNeuralNetwork/cereal/details/traits.hpp \
    recognizer/SimpleNeuralNetwork/cereal/details/util.hpp \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/error/en.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/error/error.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/biginteger.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/diyfp.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/dtoa.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/ieee754.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/itoa.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/meta.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/pow10.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/regex.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/stack.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/strfunc.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/strtod.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/internal/swap.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/msinttypes/inttypes.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/msinttypes/stdint.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/allocators.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/document.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/encodedstream.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/encodings.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/filereadstream.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/filewritestream.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/fwd.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/istreamwrapper.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/memorybuffer.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/memorystream.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/ostreamwrapper.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/pointer.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/prettywriter.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/rapidjson.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/reader.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/schema.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/stream.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/stringbuffer.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidjson/writer.h \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidxml/rapidxml.hpp \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidxml/rapidxml_iterators.hpp \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidxml/rapidxml_print.hpp \
    recognizer/SimpleNeuralNetwork/cereal/external/rapidxml/rapidxml_utils.hpp \
    recognizer/SimpleNeuralNetwork/cereal/external/base64.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/concepts/pair_associative_container.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/array.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/base_class.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/bitset.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/boost_variant.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/chrono.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/common.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/complex.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/deque.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/forward_list.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/functional.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/list.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/map.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/memory.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/polymorphic.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/queue.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/set.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/stack.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/string.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/tuple.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/unordered_map.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/unordered_set.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/utility.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/valarray.hpp \
    recognizer/SimpleNeuralNetwork/cereal/types/vector.hpp \
    recognizer/SimpleNeuralNetwork/cereal/access.hpp \
    recognizer/SimpleNeuralNetwork/cereal/cereal.hpp \
    recognizer/SimpleNeuralNetwork/cereal/macros.hpp

CONFIG(debug, debug|release) {
    DEFINES += VERBOSE TIME_PROFILING
}

CONFIG(release, debug|release) {
    DEFINES += VERBOSE TIME_PROFILING
}
