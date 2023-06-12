#include <network/packets/move_entity_packet.hpp>

const uint8_t RoadRunner::network::packets::MoveEntityPacket::packet_id = 144;

bool RoadRunner::network::packets::MoveEntityPacket::deserialize_body(RakNet::BitStream *stream) {
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

void RoadRunner::network::packets::MoveEntityPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
}
