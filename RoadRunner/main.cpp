#include <stdio.h>
#include <string.h>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <PacketPriority.h>
#include <BitStream.h>
#include <stdint.h>
#include <stdint.h>
#include <network/packets/start_game_packet.hpp>
#include <network/packets/login_status_packet.hpp>
#include <network/packets/login_packet.hpp>

#define MAX_CLIENTS 10
#define SERVER_PORT 19132

using RoadRunner::network::packets::StartGamePacket;
using RoadRunner::network::packets::LoginStatusPacket;
using RoadRunner::network::packets::LoginPacket;

template <typename T> void send_packet(T& packet, RakNet::RakPeerInterface *peer, RakNet::RakNetGUID guid) {
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, guid, false);
}

int main(void) {
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet *packet;

	RakNet::SocketDescriptor sd(SERVER_PORT,0);
	peer->Startup(MAX_CLIENTS, &sd, 1);

	printf("Starting the server.\n");

	peer->SetMaximumIncomingConnections(MAX_CLIENTS);

	while (1) {
		for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive()) {
            if (packet->bitSize != 0) {
                RakNet::BitStream receive_stream(packet->data, packet->bitSize, false);

                uint8_t packet_id;
                receive_stream.Read<uint8_t>(packet_id);

			    switch (packet_id) {		
			    	case ID_NEW_INCOMING_CONNECTION:
			    		printf("A connection is incoming.\n");
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
                        if (packet_id == LoginPacket::packet_id) {
                            LoginStatusPacket login_status;
                            login_status.status = 0;
                            send_packet(login_status, peer, packet->guid);

                            StartGamePacket start_game;
                            start_game.seed = 0;
                            start_game.forceHasResourse = 0;
                            start_game.gamemode = 0;
                            start_game.entity_id = 1;
                            start_game.x = 180.f;
                            start_game.y = 72.f;
                            start_game.z = 180.f;

                            send_packet(start_game, peer, packet->guid);
                        }
                        break;
                }
            }
		}
	}
	
	
	RakNet::RakPeerInterface::DestroyInstance(peer);

	return 0;
}