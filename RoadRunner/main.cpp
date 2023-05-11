#include <server.hpp>
#include <config.hpp>

using RoadRunner::Server;

int main(void) {
    Server *server = new Server(SERVER_PORT, MAX_CLIENTS);
}