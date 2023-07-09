#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <network/types/record_type.hpp>

using RoadRunner::network::types::RecordType;

namespace RoadRunner {
    namespace network {
        namespace packets {
            class ExplodePacket {
            public:
                static const uint8_t packet_id;

                float x;
                float y;
                float z;
                float radius;
                std::vector<RecordType> records;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}
