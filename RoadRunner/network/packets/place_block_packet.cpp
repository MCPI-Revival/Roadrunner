#include <network/packets/place_block_packet.hpp>

const uint8_t RoadRunner::network::packets::PlaceBlockPacket::packet_id = 149;

bool RoadRunner::network::packets::PlaceBlockPacket::deserialize_body(RakNet::BitStream *stream) {
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
    if (!stream->Read<uint8_t>(this->block)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->meta)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->face)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::PlaceBlockPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->z);
    stream->Write<uint8_t>(this->y);
    stream->Write<uint8_t>(this->block);
    stream->Write<uint8_t>(this->meta);
    stream->Write<uint8_t>(this->face);
}
