#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class LevelEventPacket {
            public:
                static const uint8_t packet_id;

                int16_t event_id;
                int16_t x;
                int16_t y;
                int16_t z;
                int32_t data;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
