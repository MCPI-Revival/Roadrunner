#include <network/packets/add_mob_packet.hpp>

const uint8_t RoadRunner::network::packets::AddMobPacket::packet_id = 136;

bool RoadRunner::network::packets::AddMobPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->type)) {
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
    if (!this->metadata.deserialize(stream)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::AddMobPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<int32_t>(this->type);
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
    stream->Write<int8_t>(this->pitch);
    stream->Write<int8_t>(this->yaw);
    this->metadata.serialize(stream);
}
