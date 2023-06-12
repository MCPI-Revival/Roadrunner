#include <network/packets/remove_block_packet.hpp>

const uint8_t RoadRunner::network::packets::RemoveBlockPacket::packet_id = 150;

bool RoadRunner::network::packets::RemoveBlockPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->x)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->z)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->y)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::RemoveBlockPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->z);
    stream->Write<uint8_t>(this->y);
}
