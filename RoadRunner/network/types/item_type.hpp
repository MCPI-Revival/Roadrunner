#pragma once

#include <BitStream.h>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace types {
            class ItemType {
            public:
                int16_t id;
                uint8_t count;
                int16_t aux;

                bool deserialize(RakNet::BitStream *stream);

                void serialize(RakNet::BitStream *stream);
            };
        }
    }
}