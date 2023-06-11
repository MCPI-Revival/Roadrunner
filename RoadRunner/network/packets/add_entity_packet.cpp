#include <network/packets/add_entity_packet.hpp>

const uint8_t RoadRunner::network::packets::AddEntityPacket::packet_id = 140;

bool RoadRunner::network::packets::AddEntityPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->entity_id)) {
        return false;
    }
    if (!stream->Read<int8_t>(this->type)) {
        return false;
    }
    if (!stream->Read<float>(this->x)) {
        return false;
    }
    if (!stream->Read<float>(this->y)) {
        return false;
    }
    if (!stream->Read<float>(this->z)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->did)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->speed_x)) {
        return false;
    }
    if (!stream->Read<int16_t>(this->speed_y)) {
		return false;
	}
    if (!stream->Read<int16_t>(this->speed_z)) {
		return false;
	}
    return true;
}

void RoadRunner::network::packets::AddEntityPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->entity_id);
    stream->Write<int32_t>(this->type);
    stream->Write<float>(this->x);
    stream->Write<float>(this->y);
    stream->Write<float>(this->z);
    stream->Write<int32_t>(this->did);
    stream->Write<int16_t>(this->speed_x);
    stream->Write<int16_t>(this->speed_y);
    stream->Write<int16_t>(this->speed_z);
}
