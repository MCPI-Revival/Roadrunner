#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class TileEventPacket {
            public:
                static const uint8_t packet_id;

                int32_t x;
                int32_t y;
                int32_t z;
                int32_t case_1;
                int32_t case_2;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
