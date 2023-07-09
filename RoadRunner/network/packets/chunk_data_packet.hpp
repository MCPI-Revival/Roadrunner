#pragma once

#include <BitStream.h>
#include <iostream>
#include <cstdint>
#include <world/chunk.hpp>

namespace RoadRunner {
    namespace network {
        namespace packets {
            class ChunkDataPacket {
            public:
                static const uint8_t packet_id;

                int32_t x;
                int32_t z;
                RoadRunner::world::Chunk *chunk;

                bool deserialize_body(RakNet::BitStream *stream);

                void serialize_body(RakNet::BitStream *stream);
            };
        }
    }
}