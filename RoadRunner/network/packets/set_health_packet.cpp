#include <network/packets/set_health_packet.hpp>

const uint8_t RoadRunner::network::packets::SetHealthPacket::packet_id = 168;

bool RoadRunner::network::packets::SetHealthPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->health)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::SetHealthPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->health);
}
