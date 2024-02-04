#pragma once

#include <nbt/tag/tag.hpp>
#include <iostream>

using RoadRunner::nbt::tag::Tag;

namespace RoadRunner {
    namespace nbt {
        namespace tag {
            class String : public Tag {
            public:
                std::string value;

                String();
                
                bool read(RakNet::BitStream *stream);

                void write(RakNet::BitStream *stream);
            };
        }
    }
}