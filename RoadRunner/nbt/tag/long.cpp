#include <nbt/tag/long.hpp>

RoadRunner::nbt::tag::Long::Long() {
    this->id = TagIdentifiers::LONG;
    this->name = "";
    this->value = 0;
}

bool RoadRunner::nbt::tag::Long::read(RakNet::BitStream *stream) {
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 8);
    return stream->Read<int64_t>(this->value);
}

void RoadRunner::nbt::tag::Long::write(RakNet::BitStream *stream) {
    stream->Write<int64_t>(this->value);
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 8, 8);
}