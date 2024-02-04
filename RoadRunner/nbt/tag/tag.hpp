#pragma once

#include <cstdint>
#include <iostream>
#include <BitStream.h>
#include <nbt/tag_identifiers.hpp>

using RoadRunner::nbt::TagIdentifiers;

namespace RoadRunner {
    namespace nbt {
        namespace tag {
            class Tag {
            public:
                TagIdentifiers id;
                std::string name;

                virtual bool read(RakNet::BitStream *stream) {
                    return false;
                }

                virtual void write(RakNet::BitStream *stream) = 0;
            };
        }
    }
}