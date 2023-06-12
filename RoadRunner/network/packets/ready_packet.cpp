#include <network/packets/ready_packet.hpp>

const uint8_t RoadRunner::network::packets::ReadyPacket::packet_id = 132;

bool RoadRunner::network::packets::ReadyPacket::deserialize_body(RakNet::BitStream *stream) {
	return stream->Read<uint8_t>(this->status);
}

void RoadRunner::network::packets::ReadyPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->status);
}
