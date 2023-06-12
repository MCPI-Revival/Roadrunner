#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

#include <network/types/metadata_type.hpp>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class AddMobPacket {
            public:
                static const uint8_t packet_id;

                int32_t entity_id;
                int32_t type;
                float x;
                float y;
                float z;
                int8_t pitch;
                int8_t yaw;
                RoadRunner::network::types::MetadataType metadata;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
