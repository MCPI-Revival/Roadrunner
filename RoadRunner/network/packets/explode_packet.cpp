#include <network/packets/explode_packet.hpp>

const uint8_t RoadRunner::network::packets::ExplodePacket::packet_id = 153;

bool RoadRunner::network::packets::ExplodePacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<float>(this->x)) {
        return false;
    }
    if (!stream->Read<float>(this->y)) {
        return false;
    }
    if (!stream->Read<float>(this->z)) {
        return false;
    }
    if (!stream->Read<float>(this->radius)) {
        return false;
    }
    uint32_t record_count;
    if (!stream->Read<uint32_t>(record_count)) {
        return false;
    }
    for (uint32_t i = 0; i < record_count; ++i) {
        RecordType record;
        if (!record.deserialize(stream)) {
            return false;
        }
        this->records.push_back(record);
    }
    return true;
}

void RoadRunner::network::packets::ExplodePacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
    stream->Write<float>(this->radius);
    stream->Write<uint32_t>(this->records.size());
    for (uint32_t i = 0; i < this->records.size(); ++i) {
        this->records[i].serialize(stream);
    }
}
