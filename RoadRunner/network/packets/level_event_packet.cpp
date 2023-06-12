#include <network/packets/level_event_packet.hpp>

const uint8_t RoadRunner::network::packets::LevelEventPacket::packet_id = 154;

bool RoadRunner::network::packets::LevelEventPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int16_t>(this->event_id)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->x)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->y)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->z)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->data)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::LevelEventPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int16_t>(this->event_id);
    stream->Write<int16_t>(this->x);
    stream->Write<int16_t>(this->y);
    stream->Write<int16_t>(this->z);
    stream->Write<int32_t>(this->data);
}
