#include <network/packets/add_painting_packet.hpp>

const uint8_t RoadRunner::network::packets::AddPaintingPacket::packet_id = 152;

bool RoadRunner::network::packets::AddPaintingPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
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
    if (!stream->Read<int32_t>(this->direction)) {
        return false;
    }
    if (!this->title.Deserialize(stream)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::AddPaintingPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->y);
    stream->Write<int32_t>(this->z);
    stream->Write<int32_t>(this->direction);
    this->title.Serialize(stream);
}
