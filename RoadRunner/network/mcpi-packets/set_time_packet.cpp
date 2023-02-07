#include <network/mcpi-packets/set_time_packet.hpp>

const uint8_t SetTimePacket::packet_id = 134;

bool SetTimePacket::deserialize_body(RakNet::BitStream *stream) {
    return stream->Read<uint32_t>(this->time);
}

void SetTimePacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint32_t>(this->time);
}