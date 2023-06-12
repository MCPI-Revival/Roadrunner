#include <network/packets/player_armor_equipment_packet.hpp>

const uint8_t RoadRunner::network::packets::PlayerArmorEquipmentPacket::packet_id = 160;

bool RoadRunner::network::packets::PlayerArmorEquipmentPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->slot_0)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->slot_1)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->slot_2)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->slot_3)) {
        return false;
    }
    return true;
}

void RoadRunner::network::packets::PlayerArmorEquipmentPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<uint8_t>(this->slot_0);
    stream->Write<uint8_t>(this->slot_1);
    stream->Write<uint8_t>(this->slot_2);
    stream->Write<uint8_t>(this->slot_3);
}
