#pragma once

#include <iostream>
#include <stdint.h>
#include <BitStream.h>

class LoginPacket {
public:
    static const uint8_t packet_id;

    RakNet::RakString username;
    uint32_t protocol_one;
    uint32_t protocol_two;

    bool deserialize_body(RakNet::BitStream *stream);

    void serialize_body(RakNet::BitStream *stream);
};