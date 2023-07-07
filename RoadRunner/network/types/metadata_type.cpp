#include <network/types/metadata_type.hpp>

bool RoadRunner::network::types::MetadataType::deserialize(RakNet::BitStream *stream) {
    for (;;) {
        uint8_t id_with_type;
        if (!stream->Read<uint8_t>(id_with_type)) {
            return false;
        }
        if (id_with_type == 127) {
            break;
        }
        uint8_t id = id_with_type & 0x1f;
        uint8_t type = id_with_type >> 5;
        metadata_value_t value;
        switch (type) {
        case 0:
            if (!stream->Read<int8_t>(value.b)) {
                return false;
            }
            break;
        case 1:
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 2);
            if (!stream->Read<int16_t>(value.s)) {
                return false;
            }
            break;
        case 2:
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 4);
            if (!stream->Read<int32_t>(value.i)) {
                return false;
            }
            break;
        case 3:
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 4);
            if (!stream->Read<float>(value.f)) {
                return false;
            }
            break;
        case 4:
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 2);
            if (!value.str.Deserialize(stream)) {
                return false;
            }
            break;
        case 5:
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 2);
            if (!stream->Read<int16_t>(value.item.id)) {
                return false;
            }
            if (!stream->Read<uint8_t>(value.item.count)) {
                return false;
            }
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 2);
            if (!stream->Read<int16_t>(value.item.aux)) {
                return false;
            }
            break;
        case 6:
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 4);
            if (!stream->Read<int32_t>(value.vector.x)) {
                return false;
            }
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 4);
            if (!stream->Read<int32_t>(value.vector.y)) {
                return false;
            }
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 4);
            if (!stream->Read<int32_t>(value.vector.z)) {
                return false;
            }
            break;
        }
        this->data[id].first = type;
        this->data[id].second = value;
    }
    return true;
}

void RoadRunner::network::types::MetadataType::serialize(RakNet::BitStream *stream) {
    std::map<uint8_t, std::pair<uint8_t, metadata_value_t>>::iterator it = this->data.begin();
    while (it != this->data.end()) {
        uint8_t id = it->first;
        std::pair<uint8_t, metadata_value_t> id_with_type = it->second;
        ++it;
        stream->Write<uint8_t>((id_with_type.first << 5) | (id & 0x1f));
        switch (id_with_type.first) {
        case 0:
            stream->Write<int8_t>(id_with_type.second.b);
            break;
        case 1:
            stream->Write<int16_t>(id_with_type.second.s);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 2, 2);
            break;
        case 2:
            stream->Write<int32_t>(id_with_type.second.i);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 4, 4);
            break;
        case 3:
            stream->Write<float>(id_with_type.second.i);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 4, 4);
            break;
        case 4:
            id_with_type.second.str.Serialize(stream);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 2 - id_with_type.second.str.GetLength(), 2);
            break;
        case 5:
            stream->Write<int16_t>(id_with_type.second.item.id);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 2, 2);
            stream->Write<uint8_t>(id_with_type.second.item.count);
            stream->Write<int16_t>(id_with_type.second.item.aux);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 2, 2);
            break;
        case 6:
            stream->Write<int32_t>(id_with_type.second.vector.x);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 4, 4);
            stream->Write<int32_t>(id_with_type.second.vector.y);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 4, 4);
            stream->Write<int32_t>(id_with_type.second.vector.z);
            stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 4, 4);
            break;
        }
    }
    stream->Write<uint8_t>(127u);
}