#include <network/mcpi-packets/message_packet.hpp>
#include <stdint.h>

const uint8_t MessagePacket::packet_id = 180;

bool MessagePacket::deserialize_body(RakNet::BitStream *stream) {
    return this->message.Deserialize(stream);
}

void MessagePacket::serialize_body(RakNet::BitStream *stream) {
    this->message.Serialize(stream);
}
