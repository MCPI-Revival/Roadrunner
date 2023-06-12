#include <network/packets/entity_event_packet.hpp>

const uint8_t RoadRunner::network::packets::EntityEventPacket::packet_id = 156;

bool RoadRunner::network::packets::EntityEventPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->event)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::EntityEventPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<uint8_t>(this->event);
}
