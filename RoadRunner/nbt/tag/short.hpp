#pragma once

#include <nbt/tag/tag.hpp>

using RoadRunner::nbt::tag::Tag;

namespace RoadRunner {
    namespace nbt {
        namespace tag {
            class Short : public Tag {
            public:
                int16_t value;

                Short();
                
                bool read(RakNet::BitStream *stream);

                void write(RakNet::BitStream *stream);
            };
        }
    }
}