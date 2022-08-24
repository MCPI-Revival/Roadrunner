#include <network/raknet/misc/magic.hpp>
#include <network/raknet/packet/unconnected_ping.hpp>

bool UnconnectedPing::deserialize_body() {
    if (!this->read_u64be(&this->client_timestamp)) {
        return false;
    }
    uint8_t *magic;
    if (!this->read(16, &magic)) {
        return false;
    }
    if (!Magic::validate_magic(magic)) {
        return false;
    }
    return true;
}

void UnconnectedPing::serialize_body() {
    this->write_u64be(this->client_timestamp);
    this->write(Magic::magic, 16);
}