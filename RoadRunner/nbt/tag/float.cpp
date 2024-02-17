#include <nbt/tag/float.hpp>

RoadRunner::nbt::tag::Float::Float() {
    this->id = TagIdentifiers::FLOAT;
    this->name = "";
    this->value = 0.0f;
}

bool RoadRunner::nbt::tag::Float::read(RakNet::BitStream *stream) {
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 4);
    return stream->Read<float>(this->value);
}

void RoadRunner::nbt::tag::Float::write(RakNet::BitStream *stream) {
    stream->Write<float>(this->value);
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 4, 4);
}