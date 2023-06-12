#include <network/packets/remove_player_packet.hpp>

const uint8_t RoadRunner::network::packets::RemovePlayerPacket::packet_id = 138;

bool RoadRunner::network::packets::RemovePlayerPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<uint64_t>(this->client_id)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::RemovePlayerPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<uint64_t>(this->client_id);
}
