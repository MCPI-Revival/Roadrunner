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
        bool is_running;
        RakNet::RakPeerInterface *peer;
        std::map<RakNet::RakNetGUID, RoadRunner::Player *> players;
        int32_t entity_id;
        std::vector<int32_t> reuseable_entity_ids;

        Server(uint16_t port, uint32_t max_clients);
        void post_to_chat(std::string message);
        uint32_t get_player_id();
    };
}