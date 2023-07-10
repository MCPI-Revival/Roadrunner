#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

#include <network/types/item_type.hpp>

using RoadRunner::network::types::ItemType;

namespace RoadRunner {
    namespace network {
        namespace packets {
            class AddItemEntityPacket {
            public:
                static const uint8_t packet_id;

                int32_t entity_id;
                ItemType item;
                float x;
                float y;
                float z;
                int8_t pitch;
                int8_t yaw;
                int8_t roll;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
