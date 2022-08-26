#pragma once

#include <network/raknet/packet/packet.hpp>

class MessagePacket : public Packet {
public:
    std::string message;

    bool deserialize_body();

    void serialize_body();
};