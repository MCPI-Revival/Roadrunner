#include <network/packets/add_item_entity_packet.hpp>

const uint8_t RoadRunner::network::packets::AddItemEntityPacket::packet_id = 142;

bool RoadRunner::network::packets::AddItemEntityPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!this->item.deserialize(stream)) {
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
    if (!stream->Read<int8_t>(this->roll)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::AddItemEntityPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    this->item.serialize(stream);
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
    stream->Write<int8_t>(this->pitch);
    stream->Write<int8_t>(this->yaw);
    stream->Write<int8_t>(this->roll);
}
