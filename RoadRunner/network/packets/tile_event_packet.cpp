#include <network/packets/tile_event_packet.hpp>

const uint8_t RoadRunner::network::packets::TileEventPacket::packet_id = 155;

bool RoadRunner::network::packets::TileEventPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->x)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->y)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->z)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->case_1)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->case_2)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::TileEventPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->y);
    stream->Write<int32_t>(this->z);
    stream->Write<int32_t>(this->case_1);
    stream->Write<int32_t>(this->case_2);
}
