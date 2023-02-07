#pragma once

#include <iostream>
#include <stdint.h>
#include <BitStream.h>

class StartGamePacket {
public:
    static const uint8_t packet_id;

    uint32_t seed;
    uint32_t forceHasResourse;
    uint32_t gamemode;
    uint32_t entity_id;
    float x;
    float y;
    float z;

    bool deserialize_body(RakNet::BitStream *stream);

    void serialize_body(RakNet::BitStream *stream);
};