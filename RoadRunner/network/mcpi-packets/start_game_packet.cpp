#include <network/mcpi-packets/start_game_packet.hpp>

const uint8_t StartGamePacket::packet_id = 135;

bool StartGamePacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint32_t>(this->seed)) {
        return false;
    }
    if (!stream->Read<uint32_t>(this->forceHasResourse)) {
        return false;
    }
    if (!stream->Read<uint32_t>(this->gamemode)) {
        return false;
    }
    if (!stream->Read<uint32_t>(this->entity_id)) {
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

void StartGamePacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint32_t>(this->seed);
    stream->Write<uint32_t>(this->forceHasResourse);
    stream->Write<uint32_t>(this->gamemode);
    stream->Write<uint32_t>(this->entity_id);
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
}
