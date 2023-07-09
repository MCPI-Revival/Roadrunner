#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

#include <network/types/metadata_type.hpp>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class AddEntityPacket {
            public:
                static const uint8_t packet_id;

                int32_t entity_id;
                uint8_t type;
                float x;
                float y;
                float z;
                int32_t has_motion;
                int16_t speed_x;
                int16_t speed_y;
                int16_t speed_z;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
