#include <nbt/tag/string.hpp>

RoadRunner::nbt::tag::String::String() {
    this->id = TagIdentifiers::STRING;
    this->name = "";
}

bool RoadRunner::nbt::tag::String::read(RakNet::BitStream *stream) {
    stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetReadOffset()), 2);
    uint16_t length;
    if (!stream->Read<uint16_t>(length)) {
        return false;
    }
    char *temp = new char[length + 1];
    temp[length] = '\0';
    if (!stream->ReadAlignedBytes((unsigned char *)temp, length)) {
        delete temp;
        return false;
    };
    this->value = temp;
    delete temp;
    return true;
}

void RoadRunner::nbt::tag::String::write(RakNet::BitStream *stream) {
    if (this->value.length() <= 0xffff) {
        stream->Write<uint16_t>((uint16_t)this->value.length());
        stream->EndianSwapBytes(BITS_TO_BYTES(stream->GetWriteOffset()) - 2, 2);
        stream->WriteAlignedBytes((unsigned char *)this->value.c_str(), this->value.length());
    }
}