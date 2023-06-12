#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class ContainerOpenPacket {
            public:
                static const uint8_t packet_id;

                uint8_t window_id;
                uint8_t type;
                uint8_t slot;
                RakNet::RakString title;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
