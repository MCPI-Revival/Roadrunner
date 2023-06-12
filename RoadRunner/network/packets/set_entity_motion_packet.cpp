#include <network/packets/set_entity_motion_packet.hpp>

const uint8_t RoadRunner::network::packets::SetEntityMotionPacket::packet_id = 167;

bool RoadRunner::network::packets::SetEntityMotionPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->speed_x)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->speed_y)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->speed_z)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::SetEntityMotionPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<int16_t>(this->speed_x);
    stream->Write<int16_t>(this->speed_y);
    stream->Write<int16_t>(this->speed_z);
}
