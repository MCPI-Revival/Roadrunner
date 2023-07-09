#pragma once

#include <iostream>
#include <cstdint>
#include <BitStream.h>
#include <network/types/item_type.hpp>
#include <vector>

using RoadRunner::network::types::ItemType;
namespace RoadRunner {
    namespace network {
        namespace packets {
            class SendInventoryPacket {
            public:
                static const uint8_t packet_id;
                int32_t entity_id;
                uint8_t window_id;
                std::vector<ItemType> items;

                bool deserialize_body(RakNet::BitStream *stream);
                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
