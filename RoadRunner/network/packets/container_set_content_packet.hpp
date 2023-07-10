#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>
#include <network/types/item_type.hpp>
#include <vector>

using RoadRunner::network::types::ItemType;

namespace RoadRunner {
    namespace network {
        namespace packets {
            class ContainerSetContentPacket {
            public:
                static const uint8_t packet_id;

                uint8_t window_id;
                std::vector<ItemType> items;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
