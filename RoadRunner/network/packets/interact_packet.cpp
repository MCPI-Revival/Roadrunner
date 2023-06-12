#include <network/packets/interact_packet.hpp>

const uint8_t RoadRunner::network::packets::InteractPacket::packet_id = 161;

bool RoadRunner::network::packets::InteractPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->action)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->target)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::InteractPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->action);
    stream->Write<int32_t>(this->entity_id);
    stream->Write<int32_t>(this->target);
}
