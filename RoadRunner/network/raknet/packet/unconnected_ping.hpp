#pragma once

#include <network/raknet/packet/packet.hpp>

class UnconnectedPing : public Packet {
public:
    uint64_t client_timestamp;

    bool deserialize_body();

    void serialize_body();
};