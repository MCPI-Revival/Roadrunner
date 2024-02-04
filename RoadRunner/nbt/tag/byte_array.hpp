#pragma once

#include <nbt/tag/tag.hpp>

using RoadRunner::nbt::tag::Tag;

namespace RoadRunner {
    namespace nbt {
        namespace tag {
            class ByteArray : public Tag {
            public:
                int8_t *value;
                int32_t size;

                ByteArray();

                ~ByteArray();
                
                bool read(RakNet::BitStream *stream);

                void write(RakNet::BitStream *stream);
            };
        }
    }
}