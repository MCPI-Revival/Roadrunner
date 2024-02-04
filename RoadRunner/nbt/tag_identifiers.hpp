#pragma once

#include <cstdint>

namespace RoadRunner {
    namespace nbt {
        enum class TagIdentifiers : int8_t {
            END,
            BYTE,
            SHORT,
            INT,
            LONG,
            FLOAT,
            DOUBLE,
            BYTE_ARRAY,
            STRING,
            LIST,
            COMPOUND,
            INT_ARRAY,
            LONG_ARRAY
        };
    }
}