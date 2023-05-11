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
                uint64_t client_guid;
                RakNet::RakString username;
                int32_t entity_id;
                float x;
                float y;
                float z;
                int8_t pitch;
                int8_t yaw;
                uint16_t item_id = 0;
                ;
                uint16_t item_meta = 0;
                RoadRunner::network::types::MetadataType metadata;

                bool deserialize_body(RakNet::BitStream *stream);
                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
