#include <nbt/tag/byte.hpp>

RoadRunner::nbt::tag::Byte::Byte() {
    this->id = TagIdentifiers::BYTE;
    this->name = "";
}

bool RoadRunner::nbt::tag::Byte::read(RakNet::BitStream *stream) {
    return stream->Read<int8_t>(this->value);
}

void RoadRunner::nbt::tag::Byte::write(RakNet::BitStream *stream) {
    stream->Write<int8_t>(this->value);
}