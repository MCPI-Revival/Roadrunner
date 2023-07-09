#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class PlayerArmorEquipmentPacket {
            public:
                static const uint8_t packet_id;

                int32_t entity_id;
                uint8_t slot_0;
                uint8_t slot_1;
                uint8_t slot_2;
                uint8_t slot_3;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
