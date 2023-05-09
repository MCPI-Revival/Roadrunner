#include <player.hpp>
#include <network/packets/chat_packet.hpp>
#include <network/packets/login_packet.hpp>
#include <network/packets/login_status_packet.hpp>
#include <network/packets/message_packet.hpp>
#include <network/packets/start_game_packet.hpp>

using RoadRunner::network::packets::ChatPacket;
using RoadRunner::network::packets::LoginPacket;
using RoadRunner::network::packets::LoginStatusPacket;
using RoadRunner::network::packets::MessagePacket;
using RoadRunner::network::packets::StartGamePacket;

template <typename T>
void RoadRunner::Player::send_packet(T &packet) {
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    this->server->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, this->guid, false);
}

void RoadRunner::Player::handle_packet(uint8_t packet_id, RakNet::BitStream *stream) {
    if (packet_id == LoginPacket::packet_id) {
        LoginPacket login;
        login.deserialize_body(stream);
        printf("%s has joined the game\n", login.username.C_String());

        LoginStatusPacket login_status;
        login_status.status = 0;
        this->send_packet(login_status);

        StartGamePacket start_game;
        start_game.seed = 0;
        start_game.forceHasResourse = 0;
        start_game.gamemode = 0;
        start_game.entity_id = 1;
        start_game.x = 180.f;
        start_game.y = 72.f;
        start_game.z = 180.f;

        this->send_packet(start_game);
    }
}