#include <nbt/tag/int.hpp>

RoadRunner::nbt::tag::Int::Int() {
    this->id = TagIdentifiers::INT;
}

bool RoadRunner::nbt::tag::Int::read(RakNet::BitStream *stream) {
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 4);
    return stream->Read<int32_t>(this->value);
}

void RoadRunner::nbt::tag::Int::write(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->value);
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 4, 4);
}