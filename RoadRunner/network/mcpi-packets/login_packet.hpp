#pragma once

#include <network/raknet/packet/packet.hpp>

class LoginPacket : public Packet {
public:
    std::string username;
    int protocol_one;
    int protocol_two;

    bool deserialize_body();

    void serialize_body();
};