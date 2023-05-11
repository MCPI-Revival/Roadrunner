#include <world/chunk.hpp>
#include <cstring>

RoadRunner::world::Chunk::Chunk(int32_t x, int32_t z) {
    this->x = x;
    this->z = z;
    memset(this->block_ids, 0, sizeof(this->block_ids));
    memset(this->block_metas, 0, sizeof(this->block_metas));
}

uint8_t RoadRunner::world::Chunk::get_block_id(uint32_t x, uint32_t y, uint32_t z) {
    return this->block_ids[COORDS_TO_INDEX(x, y, z)];
}

void RoadRunner::world::Chunk::set_block_id(uint32_t x, uint32_t y, uint32_t z, uint8_t block_id) {
    this->block_ids[COORDS_TO_INDEX(x, y, z)] = block_id;
}

uint8_t RoadRunner::world::Chunk::get_block_meta(uint32_t x, uint32_t y, uint32_t z) {
    return NBARR_GET(COORDS_TO_INDEX(x, y, z), this->block_metas);
}

void RoadRunner::world::Chunk::set_block_meta(uint32_t x, uint32_t y, uint32_t z, uint8_t block_meta) {
    NBARR_SET(COORDS_TO_INDEX(x, y, z), block_meta, this->block_metas);
}