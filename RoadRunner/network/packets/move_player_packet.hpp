#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

#include <network/types/metadata_type.hpp>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class MovePlayerPacket {
            public:
                static const uint8_t packet_id;
                int entity_id;
                float x;
                float y;
                float z;
                float pitch;
                float yaw;
                RoadRunner::network::types::MetadataType metadata;
                bool deserialize_body(RakNet::BitStream *stream);
                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
