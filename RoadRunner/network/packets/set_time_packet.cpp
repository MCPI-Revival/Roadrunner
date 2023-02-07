#include <network/packets/set_time_packet.hpp>

const uint8_t RoadRunner::network::packets::SetTimePacket::packet_id = 134;

bool RoadRunner::network::packets::SetTimePacket::deserialize_body(RakNet::BitStream *stream) {
    return stream->Read<uint32_t>(this->time);
}

void RoadRunner::network::packets::SetTimePacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint32_t>(this->time);
}