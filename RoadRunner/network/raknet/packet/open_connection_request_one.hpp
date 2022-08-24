#pragma once

#include <network/raknet/packet/packet.hpp>

class OpenConnectionsRequestOne : public Packet {
public:
    uint8_t protocol_version;
    uint16_t mtu_size;

    bool deserialize_body();

    void serialize_body();
};