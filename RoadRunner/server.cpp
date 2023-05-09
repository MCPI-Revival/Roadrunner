#include <server.hpp>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <PacketPriority.h>

RoadRunner::Server::Server(uint16_t port, uint32_t max_clients) {
    this->peer = RakNet::RakPeerInterface::GetInstance();

    RakNet::Packet *packet;

    RakNet::SocketDescriptor sd(port, 0);
    peer->Startup(max_clients, &sd, 1);

    printf("Starting the server.\n");

    peer->SetMaximumIncomingConnections(max_clients);

    while (1) {
        packet = peer->Receive();
        if (!packet) continue;
        if (packet->bitSize != 0) {
            RakNet::BitStream receive_stream(packet->data, packet->bitSize, false);

            uint8_t packet_id;
            receive_stream.Read<uint8_t>(packet_id);

            switch (packet_id) {
            case ID_NEW_INCOMING_CONNECTION:
                printf("A new connection is incoming.\n");
                if (this->players.count(packet->guid) == 0) {
                    RoadRunner::Player *player = new RoadRunner::Player();
                    player->guid = packet->guid;
                    player->server = this;
                    this->players[packet->guid] = player;
                }
                break;
            case ID_NO_FREE_INCOMING_CONNECTIONS:
                printf("The server is full.\n");
                break;
            case ID_DISCONNECTION_NOTIFICATION:
                printf("A client has disconnected.\n");
                if (this->players.count(packet->guid) != 0) {
                    this->players.erase(packet->guid);
                }
                break;
            case ID_CONNECTION_LOST:
                printf("A client lost the connection.\n");
                if (this->players.count(packet->guid) != 0) {
                    this->players.erase(packet->guid);
                }
                break;
            default:
                if (this->players.count(packet->guid) != 0) {
                    this->players[packet->guid]->handle_packet(packet_id, &receive_stream);
                }
                break;
            }
        }
        peer->DeallocatePacket(packet);
    }

    RakNet::RakPeerInterface::DestroyInstance(peer);
}