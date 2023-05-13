#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class PlayerEquipmentPacket {
            public:
                static const uint8_t packet_id;
                int32_t entity_id;
                int16_t item_id;
                int16_t data;

                bool deserialize_body(RakNet::BitStream *stream);
                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
