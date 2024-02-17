#include <nbt/tag/list.hpp>
#include <nbt/tag/int.hpp>
#include <nbt/tag_utils.hpp>

using RoadRunner::nbt::tag::Int;

RoadRunner::nbt::tag::List::List() {
    this->id = TagIdentifiers::LIST;
    this->name = "";
    this->value = nullptr;
    this->size = 0;
}

RoadRunner::nbt::tag::List::~List() {
    if (this->value != nullptr) {
        for (int32_t i = 0; i < this->size; ++i) {
            if (this->value[i] != nullptr) {
                delete this->value[i];
            }
        }
        delete[] this->value;
        this->value = nullptr;
        this->size = 0;
    }
}

bool RoadRunner::nbt::tag::List::read(RakNet::BitStream *stream) {
    if (!stream->Read<int8_t>(this->tag_id)) {
        return false;
    }
    Int sizeTag;
    if (!sizeTag.read(stream)) {
        return false;
    }
    this->size = sizeTag.value;
    this->value = new Tag *[this->size];
    for (int32_t i = 0; i < this->size; ++i) {
        this->value[i] = create_tag(static_cast<TagIdentifiers>(this->tag_id));
        if (!this->value[i]->read(stream)) {
            for (int32_t j = 0; j <= i; ++j) {
                if (this->value[j] != nullptr) {
                    delete this->value[j];
                }
            }
            delete[] this->value;
            this->value = nullptr;
            this->size = 0;
            return false;
        }
    }
    return true;
}

void RoadRunner::nbt::tag::List::write(RakNet::BitStream *stream) {
    if (this->size > 0 && this->value != nullptr) {
        stream->Write<int8_t>(this->tag_id);
        Int sizeTag;
        sizeTag.value = this->size;
        sizeTag.write(stream);
        for (int32_t i = 0; i < this->size; ++i) {
            this->value[i]->write(stream);
        }
    }
}