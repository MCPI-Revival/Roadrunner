#pragma once

#include <iostream>
#include <stdint.h>
#include <BitStream.h>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class SetTimePacket {
            public:
                static const uint8_t packet_id;

                int32_t time;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}