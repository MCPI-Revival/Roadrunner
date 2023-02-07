#include <network/mcpi-packets/login_status_packet.hpp>

const uint8_t LoginStatusPacket::packet_id = 131;

bool LoginStatusPacket::deserialize_body(RakNet::BitStream *stream) {
    return stream->Read<uint32_t>(this->status);
}

void LoginStatusPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint32_t>(this->status);
}
