#include <network/packets/adventure_settings_packet.hpp>

const uint8_t RoadRunner::network::packets::AdventureSettingsPacket::packet_id = 182;

bool RoadRunner::network::packets::AdventureSettingsPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint32_t>(this->flags)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::AdventureSettingsPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint32_t>(this->flags);
}
