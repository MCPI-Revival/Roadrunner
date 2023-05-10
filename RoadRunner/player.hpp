#pragma once

#include <string>

#include <BitStream.h>
#include <server.hpp>

namespace RoadRunner {
    class Server;

    class Player {
    public:
        std::string username = "???";
        int entity_id;
        RakNet::RakNetGUID guid;
        RoadRunner::Server *server;

        template <typename T>
        void send_packet(T &packet);
        template <typename T>
        void broadcast_packet(T &packet);

        void handle_packet(uint8_t packet_id, RakNet::BitStream *stream);
    };
}