#include <nbt/tag/byte_array.hpp>
#include <nbt/tag/int.hpp>

using RoadRunner::nbt::tag::Int;

RoadRunner::nbt::tag::ByteArray::ByteArray() {
    this->id = TagIdentifiers::BYTE_ARRAY;
    this->value = nullptr;
    this->size = 0;
}

RoadRunner::nbt::tag::ByteArray::~ByteArray() {
    if (this->value != nullptr) {
        delete this->value;
        this->value = nullptr;
        this->size = 0;
    }
}

bool RoadRunner::nbt::tag::ByteArray::read(RakNet::BitStream *stream) {
    Int sizeTag;
    if (!sizeTag.read(stream)) {
        return false;
    }
    this->size = sizeTag.value;
    this->value = new int8_t[this->size];
    for (int32_t i = 0; i < this->size; ++i) {
        if (!stream->Read<int8_t>(this->value[i])) {
            delete this->value;
            this->value = nullptr;
            this->size = 0;
            return false;
        }
    }
    return true;
}

void RoadRunner::nbt::tag::ByteArray::write(RakNet::BitStream *stream) {
    if (this->size > 0 && this->value != nullptr) {
        Int sizeTag;
        sizeTag.value = this->size;
        sizeTag.write(stream);
        for (int32_t i = 0; i < this->size; ++i) {
            stream->Write<int8_t>(this->value[i]);
        }
    }
}