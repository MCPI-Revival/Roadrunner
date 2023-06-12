#include <network/packets/sign_update_packet.hpp>

const uint8_t RoadRunner::network::packets::SignUpdatePacket::packet_id = 181;

bool RoadRunner::network::packets::SignUpdatePacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int16_t>(this->x)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->y)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->z)) {
        return false;
    }
    if (!this->lines.Deserialize(stream)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::SignUpdatePacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int16_t>(this->x);
    stream->Write<uint8_t>(this->y);
    stream->Write<int16_t>(this->z);
    this->lines.Serialize(stream);
}
