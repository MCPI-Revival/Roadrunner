#pragma once

#include <BitStream.h>
#include <cstdint>
#include <map>
#include <network/types/item_type.hpp>

typedef struct {
    int32_t x;
    int32_t y;
    int32_t z;
} metadata_vec_t;

typedef struct {
    int8_t b;
    int16_t s;
    int32_t i;
    float f;
    RakNet::RakString str;
    RoadRunner::network::types::ItemType item;
    metadata_vec_t vector;
} metadata_value_t;

namespace RoadRunner {
    namespace network {
        namespace types {
            class MetadataType {
            public:
                std::map<uint8_t, std::pair<uint8_t, metadata_value_t>> data;

                bool deserialize(RakNet::BitStream *stream);

                void serialize(RakNet::BitStream *stream);
            };
        }
    }
}