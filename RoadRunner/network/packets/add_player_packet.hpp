#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

#include <network/types/metadata_type.hpp>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class AddPlayerPacket {
            public:
                static const uint8_t packet_id;
                int client_guid;
                RakNet::RakString username;
                int entity_id;
                float x;
                float y;
                float z;
                int pitch;
                int yaw;
                int item_id = 0;
                int item_meta = 0;
                RoadRunner::network::types::MetadataType metadata;
                bool deserialize_body(RakNet::BitStream *stream);
                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
