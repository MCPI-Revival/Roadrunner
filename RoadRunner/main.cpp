#include <config.hpp>
#include <server.hpp>

using RoadRunner::Server;

int main(void) {
    Server *server = new Server(SERVER_PORT, MAX_CLIENTS);
}