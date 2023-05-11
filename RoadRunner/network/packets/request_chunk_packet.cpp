#include <network/packets/request_chunk_packet.hpp>

const uint8_t RoadRunner::network::packets::RequestChunkPacket::packet_id = 157;

bool RoadRunner::network::packets::RequestChunkPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->x)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->z)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::RequestChunkPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->z);
}
