#include <network/packets/adventure_settings_packet.hpp>

const uint8_t RoadRunner::network::packets::AdventureSettingsPacket::packet_id = 182;

bool RoadRunner::network::packets::AdventureSettingsPacket::deserialize_body(RakNet::BitStream *stream) {
	return stream->Read<uint32_t>(this->flags);
}

void RoadRunner::network::packets::AdventureSettingsPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint32_t>(this->flags);
}
