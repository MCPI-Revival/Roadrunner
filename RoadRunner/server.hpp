#pragma once

#include <RakPeerInterface.h>
#include <cstdint>
#include <map>
#include <player.hpp>

namespace RoadRunner {
    class Player;
    
    class Server {
    public:
        RakNet::RakPeerInterface *peer;
        std::map<RakNet::RakNetGUID, RoadRunner::Player *> players;

        Server(uint16_t port, uint32_t max_clients);
    };
}