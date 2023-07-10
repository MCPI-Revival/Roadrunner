#include <network/packets/container_set_content_packet.hpp>

const uint8_t RoadRunner::network::packets::ContainerSetContentPacket::packet_id = 178;

bool RoadRunner::network::packets::ContainerSetContentPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<uint8_t>(this->window_id)) {
        return false;
    }
    int16_t item_count = 0;
    if (!stream->Read<int16_t>(item_count)) {
        return false;
    }
    this->items.clear();
    for (int i = 0; i < item_count; i++) {
        ItemType item;
        if (!item.deserialize(stream)) {
            return false;
        }
        this->items.push_back(item);
    }
    return true;
}

void RoadRunner::network::packets::ContainerSetContentPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<uint8_t>(this->window_id);
    for (size_t i = 0; i < this->items.size(); ++i) {
        this->items[i].serialize(stream);
    }
}
