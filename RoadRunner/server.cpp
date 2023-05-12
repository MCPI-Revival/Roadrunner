#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <PacketPriority.h>

#include <network/packets/message_packet.hpp>
#include <server.hpp>

using RoadRunner::Server;
using RoadRunner::network::packets::MessagePacket;

void Server::post_to_chat(std::string message) {
    MessagePacket msg;
    msg.message = message.c_str();
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(msg.packet_id);
    msg.serialize_body(&send_stream);
    std::map<const RakNet::RakNetGUID, RoadRunner::Player *>::iterator it = this->players.begin();
    while (it != this->players.end()) {
        this->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
        ++it;
    }
}

Server::Server(uint16_t port, uint32_t max_clients) {
    this->entity_id = 1;
    this->peer = RakNet::RakPeerInterface::GetInstance();

    RakNet::Packet *packet;

    RakNet::SocketDescriptor sd(port, 0);
    peer->Startup(max_clients, &sd, 1);

    printf("Starting the server.\n");

    peer->SetMaximumIncomingConnections(max_clients);

    EntityIDGenerator idGen;
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
                    RoadRunner::Player *player = new RoadRunner::Player(this, &idGen);
                    player->guid = packet->guid;
                    if (this->reuseable_entity_ids.size()) {
                        player->entity_id = this->reuseable_entity_ids.back();
                        this->reuseable_entity_ids.pop_back();
                    } else {
                        player->entity_id = this->entity_id++;
                    }
                    this->players[packet->guid] = player;
                }
                break;
            case ID_NO_FREE_INCOMING_CONNECTIONS:
                printf("The server is full.\n");
                break;
            case ID_DISCONNECTION_NOTIFICATION:
                printf("A client has disconnected.\n");
                if (this->players.count(packet->guid) != 0) {
                    Player *player = this->players[packet->guid];
                    this->reuseable_entity_ids.push_back(player->entity_id);
                    std::string message = player->username + " has left the game";
                    this->players.erase(packet->guid);
                    puts(message.c_str());
                    this->post_to_chat(message);
                }
                break;
            case ID_CONNECTION_LOST:
                printf("A client lost the connection.\n");
                if (this->players.count(packet->guid) != 0) {
                    Player *player = this->players[packet->guid];
                    this->reuseable_entity_ids.push_back(player->entity_id);
                    std::string message = player->username + " has left the game";
                    this->players.erase(packet->guid);
                    puts(message.c_str());
                    this->post_to_chat(message);
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
