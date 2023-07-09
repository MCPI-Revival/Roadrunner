#include <network/types/record_type.hpp>

bool RoadRunner::network::types::RecordType::deserialize(RakNet::BitStream *stream) {
    if (!stream->Read<int8_t>(this->x)) {
        return false;
    }
    if (!stream->Read<int8_t>(this->y)) {
        return false;
    }
    if (!stream->Read<int8_t>(this->z)) {
        return false;
    }
    return true;
}

void RoadRunner::network::types::RecordType::serialize(RakNet::BitStream *stream) {
    stream->Write<int8_t>(this->x);
    stream->Write<int8_t>(this->y);
    stream->Write<int8_t>(this->z);
}
