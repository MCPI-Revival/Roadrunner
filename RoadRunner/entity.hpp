#pragma once

#include <vector>
#include <cstdint>

namespace RoadRunner {
    class Server;

    class EntityIDGenerator {
        std::vector<int32_t> free_ids = {};
        int32_t count = 0;
    public:
        int32_t alloc();
        void free(int32_t id);
    };


    class Entity {
    public:
        RoadRunner::Server *server;
        EntityIDGenerator *idGenerator;

        float x = 0;
        float y = 0;
        float z = 0;
        float yaw = 0;
        float pitch = 0;
        int32_t entity_id = 0;

        Entity(Server *server, EntityIDGenerator *idGenerator) :
            server(server), idGenerator(idGenerator)
        {
            entity_id = idGenerator->alloc();
        }

        ~Entity() {
            idGenerator->free(entity_id);
        }
    };
}
