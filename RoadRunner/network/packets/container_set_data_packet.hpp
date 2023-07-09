#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class ContainerSetDataPacket {
            public:
                static const uint8_t packet_id;

                uint8_t window_id;
                int16_t property;
                int16_t value;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
