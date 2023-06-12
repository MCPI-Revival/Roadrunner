#include <network/packets/update_block_packet.hpp>

const uint8_t RoadRunner::network::packets::UpdateBlockPacket::packet_id = 151;

bool RoadRunner::network::packets::UpdateBlockPacket::deserialize_body(RakNet::BitStream *stream) {
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
    return true;
}

void RoadRunner::network::packets::UpdateBlockPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->z);
    stream->Write<uint8_t>(this->y);
    stream->Write<uint8_t>(this->block);
    stream->Write<uint8_t>(this->meta);
}
