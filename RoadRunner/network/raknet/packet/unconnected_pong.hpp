#pragma once

#include <network/raknet/packet/packet.hpp>

class UnconnectedPong : public Packet {
public:
    uint64_t client_timestamp;
    uint64_t server_guid;
    std::string message;

    bool deserialize_body();

    void serialize_body();
};