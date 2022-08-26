#include <network/mcpi-packets/chat_packet.hpp>

bool ChatPacket::deserialize_body() {
    if (!this->read_string(this->message)) {
        return false;
    }
    return true;
}

void ChatPacket::serialize_body() {
    this->write_string(this->message);
}
