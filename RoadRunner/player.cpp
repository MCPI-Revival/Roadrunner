#include <config.hpp>
#include <network/packets/chat_packet.hpp>
#include <network/packets/login_packet.hpp>
#include <network/packets/login_status_packet.hpp>
#include <network/packets/message_packet.hpp>
#include <network/packets/start_game_packet.hpp>
#include <player.hpp>

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

template <typename T>
void RoadRunner::Player::broadcast_packet(T &packet) {
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    for (auto const &guid : this->server->players) {
        this->server->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, guid.first, false);
    }
}

void RoadRunner::Player::handle_packet(uint8_t packet_id, RakNet::BitStream *stream) {
    if (packet_id == LoginPacket::packet_id) {
        LoginPacket login;
        login.deserialize_body(stream);
        this->username = login.username.C_String();
        printf("%s has joined the game\n", login.username.C_String());

        // Continue the login sequence
        LoginStatusPacket login_status;
        login_status.status = 0;
        this->send_packet(login_status);

        StartGamePacket start_game;
        start_game.seed = SEED;
        start_game.forceHasResourse = 0;
        start_game.gamemode = IS_CREATIVE;
        start_game.entity_id = this->entity_id;
        start_game.x = SPAWN_X;
        start_game.y = SPAWN_Y;
        start_game.z = SPAWN_Z;
        this->send_packet(start_game);

        // Sent the join message in chat
        this->server->post_to_chat(this->username + " has joined!");
    } else if (packet_id == ChatPacket::packet_id || packet_id == MessagePacket::packet_id) {
        // WARN: Currently MessagePacket and ChatPacket are identical save the id
        // if that were to change then this needs to change accordingly
        MessagePacket msg;
        msg.deserialize_body(stream);
        std::string formatted = "<" + this->username + "> " + msg.message.C_String();
        printf("[CHAT]: %s\n", formatted.c_str());
        // Send
        msg.message = formatted.c_str();
        this->broadcast_packet(msg);
    }
}
