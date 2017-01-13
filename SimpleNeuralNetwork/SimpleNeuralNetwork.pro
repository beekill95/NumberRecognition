TEMPLATE = lib
CONFIG += staticlib c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    snndata.cpp \
    snnlayer.cpp \
    snn.cpp

HEADERS += \
    snndata.h \
    snnlayer.h \
    snnfunction.h \
    snn.h \
    cereal/archives/adapters.hpp \
    cereal/archives/binary.hpp \
    cereal/archives/json.hpp \
    cereal/archives/portable_binary.hpp \
    cereal/archives/xml.hpp \
    cereal/details/helpers.hpp \
    cereal/details/polymorphic_impl.hpp \
    cereal/details/polymorphic_impl_fwd.hpp \
    cereal/details/static_object.hpp \
    cereal/details/traits.hpp \
    cereal/details/util.hpp \
    cereal/external/rapidjson/error/en.h \
    cereal/external/rapidjson/error/error.h \
    cereal/external/rapidjson/internal/biginteger.h \
    cereal/external/rapidjson/internal/diyfp.h \
    cereal/external/rapidjson/internal/dtoa.h \
    cereal/external/rapidjson/internal/ieee754.h \
    cereal/external/rapidjson/internal/itoa.h \
    cereal/external/rapidjson/internal/meta.h \
    cereal/external/rapidjson/internal/pow10.h \
    cereal/external/rapidjson/internal/regex.h \
    cereal/external/rapidjson/internal/stack.h \
    cereal/external/rapidjson/internal/strfunc.h \
    cereal/external/rapidjson/internal/strtod.h \
    cereal/external/rapidjson/internal/swap.h \
    cereal/external/rapidjson/msinttypes/inttypes.h \
    cereal/external/rapidjson/msinttypes/stdint.h \
    cereal/external/rapidjson/allocators.h \
    cereal/external/rapidjson/document.h \
    cereal/external/rapidjson/encodedstream.h \
    cereal/external/rapidjson/encodings.h \
    cereal/external/rapidjson/filereadstream.h \
    cereal/external/rapidjson/filewritestream.h \
    cereal/external/rapidjson/fwd.h \
    cereal/external/rapidjson/istreamwrapper.h \
    cereal/external/rapidjson/memorybuffer.h \
    cereal/external/rapidjson/memorystream.h \
    cereal/external/rapidjson/ostreamwrapper.h \
    cereal/external/rapidjson/pointer.h \
    cereal/external/rapidjson/prettywriter.h \
    cereal/external/rapidjson/rapidjson.h \
    cereal/external/rapidjson/reader.h \
    cereal/external/rapidjson/schema.h \
    cereal/external/rapidjson/stream.h \
    cereal/external/rapidjson/stringbuffer.h \
    cereal/external/rapidjson/writer.h \
    cereal/external/rapidxml/rapidxml.hpp \
    cereal/external/rapidxml/rapidxml_iterators.hpp \
    cereal/external/rapidxml/rapidxml_print.hpp \
    cereal/external/rapidxml/rapidxml_utils.hpp \
    cereal/external/base64.hpp \
    cereal/types/concepts/pair_associative_container.hpp \
    cereal/types/array.hpp \
    cereal/types/base_class.hpp \
    cereal/types/bitset.hpp \
    cereal/types/boost_variant.hpp \
    cereal/types/chrono.hpp \
    cereal/types/common.hpp \
    cereal/types/complex.hpp \
    cereal/types/deque.hpp \
    cereal/types/forward_list.hpp \
    cereal/types/functional.hpp \
    cereal/types/list.hpp \
    cereal/types/map.hpp \
    cereal/types/memory.hpp \
    cereal/types/polymorphic.hpp \
    cereal/types/queue.hpp \
    cereal/types/set.hpp \
    cereal/types/stack.hpp \
    cereal/types/string.hpp \
    cereal/types/tuple.hpp \
    cereal/types/unordered_map.hpp \
    cereal/types/unordered_set.hpp \
    cereal/types/utility.hpp \
    cereal/types/valarray.hpp \
    cereal/types/vector.hpp \
    cereal/access.hpp \
    cereal/cereal.hpp \
    cereal/macros.hpp

debug {
    DEFINES += VERBOSE
}
