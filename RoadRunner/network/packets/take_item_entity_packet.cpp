#include <network/packets/take_item_entity_packet.hpp>

const uint8_t RoadRunner::network::packets::TakeItemEntityPacket::packet_id = 143;

bool RoadRunner::network::packets::TakeItemEntityPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->target)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::TakeItemEntityPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->target);
    stream->Write<int32_t>(this->entity_id);
}
