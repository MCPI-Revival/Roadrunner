#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class UpdateBlockPacket {
            public:
                static const uint8_t packet_id;

                int32_t x;
                int32_t z;
                uint8_t y;
                uint8_t block;
                uint8_t meta;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
