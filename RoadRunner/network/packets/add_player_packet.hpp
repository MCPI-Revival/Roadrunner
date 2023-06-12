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

                uint64_t client_id;
                RakNet::RakString username;
                int32_t entity_id;
                float x;
                float y;
                float z;
                int8_t pitch;
                int8_t yaw;
                int16_t item;
                int16_t meta;
                RoadRunner::network::types::MetadataType metadata;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
