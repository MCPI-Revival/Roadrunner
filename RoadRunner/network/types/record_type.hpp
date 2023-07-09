#pragma once

#include <BitStream.h>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace types {
            class RecordType {
            public:
                int8_t x;
                int8_t y;
                int8_t z;

                bool deserialize(RakNet::BitStream *stream);

                void serialize(RakNet::BitStream *stream);
            };
        }
    }
}