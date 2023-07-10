#include <network/packets/drop_item_packet.hpp>

const uint8_t RoadRunner::network::packets::DropItemPacket::packet_id = 173;

bool RoadRunner::network::packets::DropItemPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->is_death)) {
        return false;
    }
    if (!this->item.deserialize(stream)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::DropItemPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<uint8_t>(this->is_death);
    this->item.serialize(stream);
}
