#include <network/packets/container_ack_packet.hpp>

const uint8_t RoadRunner::network::packets::ContainerAckPacket::packet_id = 179;

bool RoadRunner::network::packets::ContainerAckPacket::deserialize_body(RakNet::BitStream *stream) {
    return false;
}

void RoadRunner::network::packets::ContainerAckPacket::serialize_body(RakNet::BitStream *stream) {
}
