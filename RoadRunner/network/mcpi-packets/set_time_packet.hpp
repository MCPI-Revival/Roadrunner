#pragma once

#include <iostream>
#include <stdint.h>
#include <BitStream.h>

class SetTimePacket {
public:
    static const uint8_t packet_id;

    uint32_t time;

    bool deserialize_body(RakNet::BitStream *stream);

    void serialize_body(RakNet::BitStream *stream);
};