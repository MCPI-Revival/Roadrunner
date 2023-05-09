#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <PacketPriority.h>
#include <RakPeerInterface.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <network/packets/chat_packet.hpp>
#include <network/packets/login_packet.hpp>
#include <network/packets/login_status_packet.hpp>
#include <network/packets/message_packet.hpp>
#include <network/packets/start_game_packet.hpp>

#define MAX_CLIENTS 10
#define SERVER_PORT 19132

using RoadRunner::network::packets::ChatPacket;
using RoadRunner::network::packets::LoginPacket;
using RoadRunner::network::packets::LoginStatusPacket;
using RoadRunner::network::packets::MessagePacket;
using RoadRunner::network::packets::StartGamePacket;

template <typename T>
void send_packet(T &packet, RakNet::RakPeerInterface *peer, RakNet::RakNetGUID guid) {
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, guid, false);
}

void handle_packet(
    RakNet::RakPeerInterface *peer, RakNet::BitStream &stream,
    uint8_t packet_id, RakNet::RakNetGUID guid) {
    if (packet_id == LoginPacket::packet_id) {
        LoginPacket login;
        login.deserialize_body(&stream);
        printf("%s has joined the game\n", login.username.C_String());

        LoginStatusPacket login_status;
        login_status.status = 0;
        send_packet(login_status, peer, guid);

        StartGamePacket start_game;
        start_game.seed = 0;
        start_game.forceHasResourse = 0;
        start_game.gamemode = 0;
        start_game.entity_id = 1;
        start_game.x = 180.f;
        start_game.y = 72.f;
        start_game.z = 180.f;

        send_packet(start_game, peer, guid);
    }
}

int main(void) {
    RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
    RakNet::Packet *packet;

    RakNet::SocketDescriptor sd(SERVER_PORT, 0);
    peer->Startup(MAX_CLIENTS, &sd, 1);

    printf("Starting the server.\n");

    peer->SetMaximumIncomingConnections(MAX_CLIENTS);

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
                break;
            case ID_NO_FREE_INCOMING_CONNECTIONS:
                printf("The server is full.\n");
                break;
            case ID_DISCONNECTION_NOTIFICATION:
                printf("A client has disconnected.\n");
                break;
            case ID_CONNECTION_LOST:
                printf("A client lost the connection.\n");
                break;
            default:
                handle_packet(peer, receive_stream, packet_id, packet->guid);
                break;
            }
        }
        peer->DeallocatePacket(packet);
    }

    RakNet::RakPeerInterface::DestroyInstance(peer);
}