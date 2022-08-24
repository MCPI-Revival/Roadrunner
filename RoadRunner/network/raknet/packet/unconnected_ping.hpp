#pragma once

#include "packet.hpp"

class UnconnectedPing : public Packet {
public:
    uint64_t client_timestamp;

    bool deserialize_body();

    void serialize_body();
};