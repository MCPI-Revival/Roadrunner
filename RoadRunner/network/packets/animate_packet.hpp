#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class AnimatePacket {
            public:
                static const uint8_t packet_id;
                uint8_t action;
                int32_t entity_id;

                bool deserialize_body(RakNet::BitStream *stream);
                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
