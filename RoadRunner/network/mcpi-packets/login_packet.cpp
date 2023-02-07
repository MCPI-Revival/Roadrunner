#include <network/mcpi-packets/login_packet.hpp>

const uint8_t LoginPacket::packet_id = 130;

bool LoginPacket::deserialize_body(RakNet::BitStream *stream) {

    if (!this->username.Deserialize(stream)) {
        return false;
    }
    if (!stream->Read<uint32_t>(this->protocol_one)) {
        return false;
    }
    if (!stream->Read<uint32_t>(this->protocol_two)) {
        return false;
    }
    return true;
}

void LoginPacket::serialize_body(RakNet::BitStream *stream) {
    this->username.Serialize(stream);
    stream->Write<uint32_t>(this->protocol_one);
    stream->Write<uint32_t>(this->protocol_two);
}
