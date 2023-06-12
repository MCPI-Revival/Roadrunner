#include <network/packets/set_spawn_position_packet.hpp>

const uint8_t RoadRunner::network::packets::SetSpawnPositionPacket::packet_id = 169;

bool RoadRunner::network::packets::SetSpawnPositionPacket::deserialize_body(RakNet::BitStream *stream) {
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

void RoadRunner::network::packets::SetSpawnPositionPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->z);
    stream->Write<uint8_t>(this->y);
}
