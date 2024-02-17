#pragma once

#include <nbt/tag/tag.hpp>
#include <vector>

using RoadRunner::nbt::tag::Tag;

namespace RoadRunner {
    namespace nbt {
        namespace tag {
            class Compound : public Tag {
            public:
                std::vector<Tag *> value;

                Compound();

                ~Compound();
                
                bool read(RakNet::BitStream *stream);

                void write(RakNet::BitStream *stream);
            };
        }
    }
}