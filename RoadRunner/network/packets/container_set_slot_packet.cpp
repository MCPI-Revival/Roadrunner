#include <network/packets/container_set_slot_packet.hpp>

const uint8_t RoadRunner::network::packets::ContainerSetSlotPacket::packet_id = 176;

bool RoadRunner::network::packets::ContainerSetSlotPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->window_id)) {
        return false;
    }
    if (!stream->Read<uint16_t>(this->slot)) {
        return false;
    }
    if (!this->item.deserialize(stream)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::ContainerSetSlotPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->window_id);
    stream->Write<uint16_t>(this->slot);
    this->item.serialize(stream);
}
