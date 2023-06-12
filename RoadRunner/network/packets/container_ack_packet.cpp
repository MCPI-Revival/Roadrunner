#include <network/packets/container_ack_packet.hpp>

const uint8_t RoadRunner::network::packets::ContainerAckPacket::packet_id = 179;

bool RoadRunner::network::packets::ContainerAckPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->window_id)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->unknown_1)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::ContainerAckPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->window_id);
    stream->Write<int16_t>(this->unknown_1);
}
