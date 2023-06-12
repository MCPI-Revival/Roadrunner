#include <network/packets/hurt_armor_packet.hpp>

const uint8_t RoadRunner::network::packets::HurtArmorPacket::packet_id = 165;

bool RoadRunner::network::packets::HurtArmorPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int8_t>(this->health)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::HurtArmorPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int8_t>(this->health);
}
