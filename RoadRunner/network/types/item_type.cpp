#include <network/types/item_type.hpp>

bool RoadRunner::network::types::ItemType::deserialize(RakNet::BitStream *stream) {
    if (!stream->Read<int16_t>(id)) {
        return false;
    }
    if (!stream->Read<uint8_t>(count)) {
        return false;
    }
    if (!stream->Read<int16_t>(aux)) {
        return false;
    }
    return true;
}

void RoadRunner::network::types::ItemType::serialize(RakNet::BitStream *stream) {
    stream->Write<int16_t>(id);
    stream->Write<uint8_t>(count);
    stream->Write<int16_t>(aux);
}
