#include <network/packets/container_set_data_packet.hpp>

const uint8_t RoadRunner::network::packets::ContainerSetDataPacket::packet_id = 177;

bool RoadRunner::network::packets::ContainerSetDataPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->window_id)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->property)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->value)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::ContainerSetDataPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->window_id);
    stream->Write<int16_t>(this->property);
    stream->Write<int16_t>(this->value);
}
