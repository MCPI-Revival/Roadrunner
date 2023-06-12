#include <network/packets/use_item_packet.hpp>

const uint8_t RoadRunner::network::packets::UseItemPacket::packet_id = 162;

bool RoadRunner::network::packets::UseItemPacket::deserialize_body(RakNet::BitStream *stream) {
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
    if (!stream->Read<uint16_t>(this->block)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->meta)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<float>(this->fx)) {
        return false;
    }
    if (!stream->Read<float>(this->fy)) {
        return false;
    }
    if (!stream->Read<float>(this->fz)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::UseItemPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->y);
    stream->Write<int32_t>(this->z);
    stream->Write<int32_t>(this->face);
    stream->Write<uint16_t>(this->block);
    stream->Write<uint8_t>(this->meta);
    stream->Write<int32_t>(this->entity_id);
    stream->Write<float>(this->fx);
    stream->Write<float>(this->fy);
    stream->Write<float>(this->fz);
}
