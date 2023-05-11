#include <config.hpp>
#include <network/packets/chat_packet.hpp>
#include <network/packets/login_packet.hpp>
#include <network/packets/login_status_packet.hpp>
#include <network/packets/message_packet.hpp>
#include <network/packets/move_player_packet.hpp>
#include <network/packets/start_game_packet.hpp>
#include <network/packets/request_chunk_packet.hpp>
#include <network/packets/chunk_data_packet.hpp>
#include <player.hpp>

using RoadRunner::network::packets::ChatPacket;
using RoadRunner::network::packets::LoginPacket;
using RoadRunner::network::packets::LoginStatusPacket;
using RoadRunner::network::packets::MessagePacket;
using RoadRunner::network::packets::MovePlayerPacket;
using RoadRunner::network::packets::StartGamePacket;
using RoadRunner::network::packets::RequestChunkPacket;
using RoadRunner::network::packets::ChunkDataPacket;

template <typename T>
void RoadRunner::Player::send_packet(T &packet) {
    // Send a packet to the player
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    this->server->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, this->guid, false);
}

template <typename T>
void RoadRunner::Player::broadcast_packet(T &packet) {
    // Send a packet to all players
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    for (auto const &guid : this->server->players) {
        this->server->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, guid.first, false);
    }
}

template <typename T>
void RoadRunner::Player::broadcast_except_packet(T &packet) {
    // Send a packet to all players except the one sending it
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    for (auto const &guid : this->server->players) {
        if (guid.first == this->guid) continue;
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
    } else if (packet_id == MovePlayerPacket::packet_id) {
        MovePlayerPacket move_player;
        move_player.deserialize_body(stream);
        bool valid = true;
        // Ensure entity id is that of the player
        if (move_player.entity_id != this->entity_id) {
            // Attempt to move a diffrent entity
            return;
        }
#if WORLD_BORDER
        // Make sure it doesn't go over the world border (X/Z)
        if (move_player.x < 0.f) {
            move_player.x = 0.f;
            valid = false;
        } else if (move_player.x > 256.f) {
            move_player.x = 256.f;
            valid = false;
        }
        if (move_player.z < 0.f) {
            move_player.z = 0.f;
            valid = false;
        } else if (move_player.z > 256.f) {
            move_player.z = 256.f;
            valid = false;
        }
#endif
        // Make sure it isn't a teleport
        // TODO: Check dy and give fall damage as needed
        int dx = abs(move_player.x - this->x);
        if (dx > MAX_DIST) {
            this->x += std::signbit(this->x - move_player.x) * MAX_DIST;
            move_player.x = this->x;
            valid = false;
        }
        int dz = abs(move_player.z - this->z);
        if (dz > MAX_DIST) {
            this->z += std::signbit(this->z - move_player.z) * MAX_DIST;
            move_player.z = this->z;
            valid = false;
        }
        // Send
        if (valid) {
            this->broadcast_except_packet(move_player);
        } else {
            this->broadcast_packet(move_player);
        }
        // Update pos
        this->x = move_player.x;
        this->y = move_player.y;
        this->z = move_player.z;
    } else if (packet_id == RequestChunkPacket::packet_id) {
        RequestChunkPacket request_chunk;
        request_chunk.deserialize_body(stream);

        ChunkDataPacket chunk_data;
        chunk_data.x = request_chunk.x;
        chunk_data.z = request_chunk.z;
        chunk_data.chunk = new RoadRunner::world::Chunk(chunk_data.x, chunk_data.z);
        for (int32_t x = 0; x < 16; ++x) {
            for (int32_t z = 0; z < 16; ++z) {
                chunk_data.chunk->set_block_id(x, 0, z, 7);
                chunk_data.chunk->set_block_id(x, 1, z, 3);
                chunk_data.chunk->set_block_id(x, 2, z, 3);
                chunk_data.chunk->set_block_id(x, 3, z, 2);
            }
        }
        this->send_packet(chunk_data);
    }
}
