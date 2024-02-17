#include <nbt/tag/compound.hpp>
#include <nbt/tag/string.hpp>
#include <nbt/tag_utils.hpp>

using RoadRunner::nbt::tag::String;

RoadRunner::nbt::tag::Compound::Compound() {
    this->id = TagIdentifiers::COMPOUND;
    this->name = "";
}

RoadRunner::nbt::tag::Compound::~Compound() {
    for (size_t i = 0; i < this->value.size(); ++i) {
        if (this->value[i] != nullptr) {
            delete this->value[i];
        }
    }
    this->value.clear();
}

bool RoadRunner::nbt::tag::Compound::read(RakNet::BitStream *stream) {
    int8_t tag_id = 0;
    for (;;) {
        if (stream->Read<int8_t>(tag_id)) {
            if (static_cast<TagIdentifiers>(tag_id) == TagIdentifiers::END) {
                break;
            }
            String name_tag;
            if (name_tag.read(stream)) {
                Tag *tag = create_tag(static_cast<TagIdentifiers>(tag_id));
                if (tag != nullptr) {
                    tag->name = name_tag.value;
                    this->value.push_back(tag);
                    continue;
                }
            }
        }
        for (size_t i = 0; i < this->value.size(); ++i) {
            if (this->value[i] != nullptr) {
                delete this->value[i];
            }
        }
        this->value.clear();
    }
    return true;
}

void RoadRunner::nbt::tag::Compound::write(RakNet::BitStream *stream) {
    for (size_t i = 0; i < this->value.size(); ++i) {
        stream->Write<int8_t>(static_cast<int8_t>(this->value[i]->id));
        String name_tag;
        name_tag.value = this->value[i]->name;
        name_tag.write(stream);
        this->value[i]->write(stream);
    }
    stream->Write<int8_t>(static_cast<int8_t>(TagIdentifiers::END));
}