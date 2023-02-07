#include <network/mcpi-packets/ready_packet.hpp>

const uint8_t ReadyPacket::packet_id = 132;

bool ReadyPacket::deserialize_body(RakNet::BitStream *stream) {
    return stream->Read<uint8_t>(this->status);
}

void ReadyPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->status);
}
