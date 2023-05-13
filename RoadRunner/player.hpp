#pragma once

#include <string>

#include <BitStream.h>
#include <config.hpp>
#include <entity.hpp>
#include <server.hpp>

namespace RoadRunner {
    class Server;

    class Player : public Entity {
    public:
        RakNet::RakNetGUID guid;
        std::string username = "???";

        template <typename T>
        void send_packet(T &packet);
        template <typename T>
        void broadcast_packet(T &packet);
        template <typename T>
        void broadcast_except_packet(T &packet);

        void handle_packet(uint8_t packet_id, RakNet::BitStream *stream);

        Player(Server *server, EntityIDGenerator *idGenerator)
            : Entity(server, idGenerator) {
        }

        ~Player();
    };
}
