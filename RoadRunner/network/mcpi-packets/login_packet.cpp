#include <network/mcpi-packets/login_packet.hpp>

bool LoginPacket::deserialize_body() {
    if (!this->read_string(this->username)) {
        return false;
    }
    if (!this->read_i32be(&this->protocol_one)) {
        return false;
    }
    if (!this->read_i32be(&this->protocol_two)) {
        return false;
    }
    return true;
}

void LoginPacket::serialize_body() {
    this->write_string(this->username);
    this->write_i32be(this->protocol_one);
    this->write_i32be(this->protocol_two);
}
