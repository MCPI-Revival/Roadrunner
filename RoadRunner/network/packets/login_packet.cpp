#include <network/packets/login_packet.hpp>

const uint8_t RoadRunner::network::packets::LoginPacket::packet_id = 130;

bool RoadRunner::network::packets::LoginPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!this->username.Deserialize(stream)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->protocol_1)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->protocol_2)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::LoginPacket::serialize_body(RakNet::BitStream *stream) {
    this->username.Serialize(stream);
    stream->Write<int32_t>(this->protocol_1);
    stream->Write<int32_t>(this->protocol_2);
}
