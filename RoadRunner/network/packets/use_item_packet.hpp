#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class UseItemPacket {
            public:
                static const uint8_t packet_id;

                int32_t x;
                int32_t y;
                int32_t z;
                int32_t face;
                uint16_t block;
                uint8_t meta;
                int32_t entity_id;
                float fx;
                float fy;
                float fz;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
