#include <network/packets/chunk_data_packet.hpp>

using RoadRunner::world::Chunk;

const uint8_t RoadRunner::network::packets::ChunkDataPacket::packet_id = 158;

bool RoadRunner::network::packets::ChunkDataPacket::deserialize_body(RakNet::BitStream *stream) {
    if (!stream->Read<int32_t>(this->x)) {
        return false;
    }
    if (!stream->Read<int32_t>(this->z)) {
        return false;
    }
    this->chunk = new Chunk(this->x, this->z);
    for (int32_t z = 0; z < 16; ++z) {
        for (int32_t x = 0; x < 16; ++x) {
            uint8_t flags;
            if (!stream->Read<uint8_t>(flags)) {
                return false;
            }
            if (flags) {
                for (uint8_t y = 0; y < 8; ++y) {
                    if ((flags >> y) & 1) {
                        uint32_t index = COORDS_TO_INDEX(x, y << 4, z);
                        uint8_t block_ids[16];
                        if(!stream->ReadAlignedBytes(block_ids, 16)) {
                            return false;
                        }
                        memcpy(&this->chunk->block_ids[index], block_ids, 16);
                        uint8_t block_metas[8];
                        if(!stream->ReadAlignedBytes(block_metas, 8)) {
                            return false;
                        }
                        memcpy(&this->chunk->block_metas[index], block_metas, 8);
                    }
                }
            }
        }
    }
    return true;
}

void RoadRunner::network::packets::ChunkDataPacket::serialize_body(RakNet::BitStream *stream) {
    stream->Write<int32_t>(this->x);
    stream->Write<int32_t>(this->z);
    if (this->chunk != NULL) {
        for (int32_t z = 0; z < 16; ++z) {
            for (int32_t x = 0; x < 16; ++x) {
                stream->Write<uint8_t>(0xffu);
                for (uint8_t y = 0; y < 8; ++y) {
                    uint32_t index = COORDS_TO_INDEX(x, y << 4, z);
                    stream->WriteAlignedBytes(&this->chunk->block_ids[index], 16);
                    stream->WriteAlignedBytes(&this->chunk->block_metas[index >> 1], 8);
                }
            }
        }
    }
}
