#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class SignUpdatePacket {
            public:
                static const uint8_t packet_id;

                int16_t x;
                uint8_t y;
                int16_t z;
                RakNet::RakString lines;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
