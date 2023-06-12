#include <network/packets/start_game_packet.hpp>

const uint8_t RoadRunner::network::packets::StartGamePacket::packet_id = 135;

bool RoadRunner::network::packets::StartGamePacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->seed)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->generator)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->gamemode)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->entity_id)) {
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
    return true;
}

void RoadRunner::network::packets::StartGamePacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->seed);
    stream->Write<int32_t>(this->generator);
    stream->Write<int32_t>(this->gamemode);
    stream->Write<int32_t>(this->entity_id);
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
}
