#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class PlaceBlockPacket {
            public:
                static const uint8_t packet_id;

                int32_t entity_id;
                int32_t x;
                int32_t z;
                uint8_t y;
                uint8_t block;
                uint8_t meta;
                uint8_t face;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
