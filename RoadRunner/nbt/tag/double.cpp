#include <nbt/tag/double.hpp>

RoadRunner::nbt::tag::Double::Double() {
    this->id = TagIdentifiers::DOUBLE;
}

bool RoadRunner::nbt::tag::Double::read(RakNet::BitStream *stream) {
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 8);
    return stream->Read<double>(this->value);
}

void RoadRunner::nbt::tag::Double::write(RakNet::BitStream *stream) {
    stream->Write<double>(this->value);
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 8, 8);
}