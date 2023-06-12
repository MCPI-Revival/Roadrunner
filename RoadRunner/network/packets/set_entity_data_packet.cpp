#include <network/packets/set_entity_data_packet.hpp>

const uint8_t RoadRunner::network::packets::SetEntityDataPacket::packet_id = 166;

bool RoadRunner::network::packets::SetEntityDataPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!this->metadata.deserialize(stream)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::SetEntityDataPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    this->metadata.serialize(stream);
}
