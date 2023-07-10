#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>
#include <network/types/item_type.hpp>

using RoadRunner::network::types::ItemType;

namespace RoadRunner {
    namespace network {
        namespace packets {
            class ContainerSetSlotPacket {
            public:
                static const uint8_t packet_id;

                uint8_t window_id;
                uint16_t slot;
                ItemType item;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
