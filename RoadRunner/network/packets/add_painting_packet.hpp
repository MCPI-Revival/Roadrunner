#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class AddPaintingPacket {
            public:
                static const uint8_t packet_id;

                int32_t entity_id;
                int32_t x;
                int32_t y;
                int32_t z;
                int32_t direction;
                RakNet::RakString title;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
