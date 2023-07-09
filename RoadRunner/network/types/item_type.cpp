#include <network/types/item_type.hpp>

bool RoadRunner::network::types::ItemType::deserialize(RakNet::BitStream *stream) {
    if (!stream->Read<int16_t>(this->id)) {
        return false;
    }
    if (!stream->Read<uint8_t>(this->count)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->aux)) {
        return false;
    }
    return true;
}

void RoadRunner::network::types::ItemType::serialize(RakNet::BitStream *stream) {
    stream->Write<int16_t>(this->id);
    stream->Write<uint8_t>(this->count);
    stream->Write<int16_t>(this->aux);
}
