#include <network/packets/container_open_packet.hpp>

const uint8_t RoadRunner::network::packets::ContainerOpenPacket::packet_id = 174;

bool RoadRunner::network::packets::ContainerOpenPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->window_id)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->type)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->slot)) {
        return false;
    }
    if (!this->title.Deserialize(stream)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::ContainerOpenPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->window_id);
    stream->Write<uint8_t>(this->type);
    stream->Write<uint8_t>(this->slot);
    this->title.Serialize(stream);
}
