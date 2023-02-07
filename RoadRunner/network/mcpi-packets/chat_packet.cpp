#include <network/mcpi-packets/chat_packet.hpp>
#include <stdint.h>

const uint8_t ChatPacket::packet_id = 180;

bool ChatPacket::deserialize_body(RakNet::BitStream *stream) {
    return this->message.Deserialize(stream);
}

void ChatPacket::serialize_body(RakNet::BitStream *stream) {
    this->message.Serialize(stream);
}
