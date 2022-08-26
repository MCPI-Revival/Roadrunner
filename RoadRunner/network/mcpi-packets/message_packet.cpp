#include <network/mcpi-packets/message_packet.hpp>

bool MessagePacket::deserialize_body() {
    if (!this->read_string(this->message)) {
        return false;
    }
    return true;
}

void MessagePacket::serialize_body() {
    this->write_string(this->message);
}
