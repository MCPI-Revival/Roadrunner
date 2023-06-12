#include <network/packets/player_action_packet.hpp>

const uint8_t RoadRunner::network::packets::PlayerActionPacket::packet_id = 163;

bool RoadRunner::network::packets::PlayerActionPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->action)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->x)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->y)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->z)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->face)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::PlayerActionPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->action);
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->y);
    stream->Write<int32_t>(this->z);
    stream->Write<int32_t>(this->face);
    stream->Write<int32_t>(this->entity_id);
}
