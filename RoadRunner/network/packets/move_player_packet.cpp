#include <network/packets/move_player_packet.hpp>

const uint8_t RoadRunner::network::packets::MovePlayerPacket::packet_id = 148;

bool RoadRunner::network::packets::MovePlayerPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<float>(this->x)) {
        return false;
    }
    if (!stream->Read<float>(this->y)) {
        return false;
    }
    if (!stream->Read<float>(this->z)) {
        return false;
    }
    if (!stream->Read<float>(this->pitch)) {
        return false;
    }
    if (!stream->Read<float>(this->yaw)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::MovePlayerPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int>(this->entity_id);
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
    stream->Write<float>(this->pitch);
    stream->Write<float>(this->yaw);
    this->metadata.serialize(stream);
}
