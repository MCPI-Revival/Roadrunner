#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class RemoveBlockPacket {
            public:
                static const uint8_t packet_id;

                int32_t entity_id;
                int32_t x;
                int32_t z;
                uint8_t y;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
