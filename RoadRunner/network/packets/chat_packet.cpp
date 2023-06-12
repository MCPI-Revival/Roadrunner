#include <network/packets/chat_packet.hpp>

const uint8_t RoadRunner::network::packets::ChatPacket::packet_id = 180;

bool RoadRunner::network::packets::ChatPacket::deserialize_body(RakNet::BitStream *stream) {
    return this->message.Deserialize(stream);
}

void RoadRunner::network::packets::ChatPacket::serialize_body(RakNet::BitStream *stream) {
    this->message.Serialize(stream);
}
