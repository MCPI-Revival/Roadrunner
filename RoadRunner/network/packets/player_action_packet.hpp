#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class PlayerActionPacket {
            public:
                static const uint8_t packet_id;

                int32_t action;
                int32_t x;
                int32_t y;
                int32_t z;
                int32_t face;
                int32_t entity_id;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
