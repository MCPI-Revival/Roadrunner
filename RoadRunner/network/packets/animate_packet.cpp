#include <network/packets/animate_packet.hpp>

const uint8_t RoadRunner::network::packets::AnimatePacket::packet_id = 170;

bool RoadRunner::network::packets::AnimatePacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->action)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::AnimatePacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->action);
    stream->Write<int32_t>(this->entity_id);
}
