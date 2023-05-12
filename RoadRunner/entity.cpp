#include <entity.hpp>

using RoadRunner::EntityIDGenerator;

int32_t EntityIDGenerator::alloc() {
    if (this->free_ids.size() == 0) {
        this->count++;
        return this->count;
    }
    int32_t last = this->free_ids.back();
    this->free_ids.pop_back();
    return last;
}

void EntityIDGenerator::free(int32_t id) {
    if (id == this->count) {
        this->count--;
    } else {
        this->free_ids.push_back(id);
    }
}
