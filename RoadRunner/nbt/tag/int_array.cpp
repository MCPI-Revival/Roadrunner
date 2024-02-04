#include <nbt/tag/int_array.hpp>
#include <nbt/tag/int.hpp>

using RoadRunner::nbt::tag::Int;

RoadRunner::nbt::tag::IntArray::IntArray() {
    this->id = TagIdentifiers::INT_ARRAY;
    this->value = nullptr;
}

RoadRunner::nbt::tag::IntArray::~IntArray() {
    if (this->value != nullptr) {
        delete this->value;
        this->value = nullptr;
        this->size = 0;
    }
}

bool RoadRunner::nbt::tag::IntArray::read(RakNet::BitStream *stream) {
    Int sizeTag;
    if (!sizeTag.read(stream)) {
        return false;
    }
    this->size = sizeTag.value;
    this->value = new int32_t[this->size];
    for (int32_t i = 0; i < this->size; ++i) {
        Int valueTag;
        if (!valueTag.read(stream)) {
            delete this->value;
            this->value = nullptr;
            this->size = 0;
            return false;
        }
        this->value[i] = valueTag.value;
    }
    return true;
}

void RoadRunner::nbt::tag::IntArray::write(RakNet::BitStream *stream) {
    if (this->size > 0 && this->value != nullptr) {
        Int sizeTag;
        sizeTag.value = this->size;
        sizeTag.write(stream);
        for (int32_t i = 0; i < this->size; ++i) {
            Int valueTag;
            valueTag.value = this->value[i];
            valueTag.write(stream);
        }
    }
}