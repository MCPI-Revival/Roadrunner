#include <network/packets/send_inventory_packet.hpp>

const uint8_t RoadRunner::network::packets::SendInventoryPacket::packet_id = 172;

bool RoadRunner::network::packets::SendInventoryPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->window_id)) {
        return false;
    }
    int16_t count = 0;
    if (!stream->Read<int16_t>(count)) {
        return false;
    }
    this->items.clear();
    // +4 because of armor slots
    for (int i = 0; i < count + 4; i++) {
        ItemType new_item;
        if (!new_item.deserialize(stream)) {
            return false;
        }
        this->items.push_back(new_item);
    }
    return true;
}

void RoadRunner::network::packets::SendInventoryPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<uint8_t>(this->window_id);
    stream->Write<int16_t>(this->items.size() - 4);
    for (ItemType &i : items) {
        i.serialize(stream);
    }
}
