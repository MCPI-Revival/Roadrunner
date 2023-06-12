#include <network/packets/container_close_packet.hpp>

const uint8_t RoadRunner::network::packets::ContainerClosePacket::packet_id = 175;

bool RoadRunner::network::packets::ContainerClosePacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->window_id)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::ContainerClosePacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->window_id);
}
