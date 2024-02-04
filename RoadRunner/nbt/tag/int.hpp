#pragma once

#include <nbt/tag/tag.hpp>

using RoadRunner::nbt::tag::Tag;

namespace RoadRunner {
    namespace nbt {
        namespace tag {
            class Int : public Tag {
            public:   
                int32_t value;

                Int();
                
                bool read(RakNet::BitStream *stream);

                void write(RakNet::BitStream *stream);
            };
        }
    }
}