#pragma once

#include <RakPeerInterface.h>
#include <cstdint>
#include <map>
#include <player.hpp>
#include <vector>

namespace RoadRunner {
    class Player;

    class Server {
    public:
        RakNet::RakPeerInterface *peer;
        std::map<RakNet::RakNetGUID, RoadRunner::Player *> players;
        std::vector<uint8_t> ids;

        Server(uint16_t port, uint32_t max_clients);
        void post_to_chat(std::string message);
        uint32_t get_player_id();
    };
}