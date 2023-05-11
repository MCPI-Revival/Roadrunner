#pragma once

#include <string>

#include <BitStream.h>
#include <config.hpp>
#include <server.hpp>

namespace RoadRunner {
    class Server;

    class Player {
    public:
        RakNet::RakNetGUID guid;
        RoadRunner::Server *server;

        std::string username = "???";
        float x = SPAWN_X;
        float y = SPAWN_Y;
        float z = SPAWN_Z;
        float yaw = 0;
        float pitch = 0;
        int32_t entity_id = 0;

        template <typename T>
        void send_packet(T &packet);
        template <typename T>
        void broadcast_packet(T &packet);
        template <typename T>
        void broadcast_except_packet(T &packet);

        void handle_packet(uint8_t packet_id, RakNet::BitStream *stream);
    };
}
