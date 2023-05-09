#include <server.hpp>

#define MAX_CLIENTS 10
#define SERVER_PORT 19132

using RoadRunner::Server;

int main(void) {
    Server *server = new Server(SERVER_PORT, MAX_CLIENTS);
}