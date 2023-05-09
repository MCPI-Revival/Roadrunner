#pragma once

#include <BitStream.h>
#include <iostream>
#include <stdint.h>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class LoginPacket {
            public:
                static const uint8_t packet_id;

                RakNet::RakString username;
                int32_t protocol_one;
                int32_t protocol_two;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}