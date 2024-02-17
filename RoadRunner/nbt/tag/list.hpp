#pragma once

#include <nbt/tag/tag.hpp>

using RoadRunner::nbt::tag::Tag;

namespace RoadRunner {
    namespace nbt {
        namespace tag {
            class List : public Tag {
            public:
                Tag **value;
                int32_t size;
                int8_t tag_id;

                List();

                ~List();
                
                bool read(RakNet::BitStream *stream);

                void write(RakNet::BitStream *stream);
            };
        }
    }
}