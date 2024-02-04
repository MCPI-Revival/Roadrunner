#include <nbt/tag/short.hpp>

RoadRunner::nbt::tag::Short::Short() {
    this->id = TagIdentifiers::SHORT;
}

bool RoadRunner::nbt::tag::Short::read(RakNet::BitStream *stream) {
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 2);
    return stream->Read<int16_t>(this->value);
}

void RoadRunner::nbt::tag::Short::write(RakNet::BitStream *stream) {
    stream->Write<int16_t>(this->value);
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 2, 2);
}