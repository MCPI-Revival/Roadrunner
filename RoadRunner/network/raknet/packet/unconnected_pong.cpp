#include <network/raknet/misc/magic.hpp>
#include <network/raknet/packet/unconnected_pong.hpp>

bool UnconnectedPong::deserialize_body() {
    if (!this->read_u64be(&this->client_timestamp)) {
        return false;
    }
    if (!this->read_u64be(&this->server_guid)) {
        return false;
    }
    uint8_t *magic;
    if (!this->read(16, &magic)) {
        return false;
    }
    if (!Magic::validate_magic(magic)) {
        return false;
    }
    if (!this->read_string(this->message)) {
        return false;
    }
    return true;
}

void UnconnectedPong::serialize_body() {
    this->write_u64be(this->client_timestamp);
    this->write_u64be(this->server_guid);
    this->write(Magic::magic, 16);
    this->write_string(this->message);
}