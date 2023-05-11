#include <network/packets/add_player_packet.hpp>

const uint8_t RoadRunner::network::packets::AddPlayerPacket::packet_id = 137;

bool RoadRunner::network::packets::AddPlayerPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint64_t>(this->client_guid)) {
        return false;
    }
    if (!this->username.Deserialize(stream)) {
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
    if (!stream->Read<int8_t>(this->pitch)) {
        return false;
    }
    if (!stream->Read<int8_t>(this->yaw)) {
        return false;
    }
    if (!stream->Read<uint16_t>(this->item_id)) {
        return false;
    }
    if (!stream->Read<uint16_t>(this->item_meta)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::AddPlayerPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint64_t>(this->client_guid);
    this->username.Serialize(stream);
    stream->Write<int32_t>(this->entity_id);
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
    stream->Write<int8_t>(this->pitch);
    stream->Write<int8_t>(this->yaw);
    stream->Write<uint16_t>(this->item_id);
    stream->Write<uint16_t>(this->item_meta);
    this->metadata.serialize(stream);
}
