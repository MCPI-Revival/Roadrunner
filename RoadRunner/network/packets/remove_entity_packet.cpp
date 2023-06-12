#include <network/packets/remove_entity_packet.hpp>

const uint8_t RoadRunner::network::packets::RemoveEntityPacket::packet_id = 141;

bool RoadRunner::network::packets::RemoveEntityPacket::deserialize_body(RakNet::BitStream *stream) {
	return stream->Read<int32_t>(this->entity_id);
}

void RoadRunner::network::packets::RemoveEntityPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
}
