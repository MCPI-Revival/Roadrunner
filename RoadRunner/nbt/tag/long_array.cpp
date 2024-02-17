#include <nbt/tag/long_array.hpp>
#include <nbt/tag/int.hpp>
#include <nbt/tag/long.hpp>

using RoadRunner::nbt::tag::Int;
using RoadRunner::nbt::tag::Long;

RoadRunner::nbt::tag::LongArray::LongArray() {
    this->id = TagIdentifiers::LONG_ARRAY;
    this->name = "";
    this->value = nullptr;
}

RoadRunner::nbt::tag::LongArray::~LongArray() {
    if (this->value != nullptr) {
        delete[] this->value;
        this->value = nullptr;
        this->size = 0;
    }
}

bool RoadRunner::nbt::tag::LongArray::read(RakNet::BitStream *stream) {
    Int sizeTag;
    if (!sizeTag.read(stream)) {
        return false;
    }
    this->size = sizeTag.value;
    this->value = new int64_t[this->size];
    for (int32_t i = 0; i < this->size; ++i) {
        Long valueTag;
        if (!valueTag.read(stream)) {
            delete[] this->value;
            this->value = nullptr;
            this->size = 0;
            return false;
        }
        this->value[i] = valueTag.value;
    }
    return true;
}

void RoadRunner::nbt::tag::LongArray::write(RakNet::BitStream *stream) {
    if (this->size > 0 && this->value != nullptr) {
        Int sizeTag;
        sizeTag.value = this->size;
        sizeTag.write(stream);
        for (int32_t i = 0; i < this->size; ++i) {
            Long valueTag;
            valueTag.value = this->value[i];
            valueTag.write(stream);
        }
    }
}