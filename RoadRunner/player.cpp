#include <config.hpp>
#include <network/packets/add_player_packet.hpp>
#include <network/packets/chat_packet.hpp>
#include <network/packets/login_packet.hpp>
#include <network/packets/login_status_packet.hpp>
#include <network/packets/message_packet.hpp>
#include <network/packets/move_player_packet.hpp>
#include <network/packets/ready_packet.hpp>
#include <network/packets/start_game_packet.hpp>
#include <network/packets/request_chunk_packet.hpp>
#include <network/packets/chunk_data_packet.hpp>
#include <player.hpp>
#include <world/perlin.hpp>

using RoadRunner::network::packets::AddPlayerPacket;
using RoadRunner::network::packets::ChatPacket;
using RoadRunner::network::packets::LoginPacket;
using RoadRunner::network::packets::LoginStatusPacket;
using RoadRunner::network::packets::MessagePacket;
using RoadRunner::network::packets::MovePlayerPacket;
using RoadRunner::network::packets::ReadyPacket;
using RoadRunner::network::packets::StartGamePacket;
using RoadRunner::network::packets::RequestChunkPacket;
using RoadRunner::network::packets::ChunkDataPacket;
using RoadRunner::world::Perlin;

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
    std::map<const RakNet::RakNetGUID, RoadRunner::Player *>::iterator it = this->server->players.begin();
    while (it != this->server->players.end()) {
        this->server->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
        ++it;
    }
}

template <typename T>
void RoadRunner::Player::broadcast_except_packet(T &packet) {
    // Send a packet to all players except the one sending it
    RakNet::BitStream send_stream;
    send_stream.Write<uint8_t>(packet.packet_id);
    packet.serialize_body(&send_stream);
    std::map<const RakNet::RakNetGUID, RoadRunner::Player *>::iterator it = this->server->players.begin();
    while (it != this->server->players.end()) {
        if (it->first == this->guid) {
            ++it;
            continue;
        }
        this->server->peer->Send(&send_stream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, 0, it->first, false);
        ++it;
    }
}

void RoadRunner::Player::handle_packet(uint8_t packet_id, RakNet::BitStream *stream) {
    if (packet_id == LoginPacket::packet_id) {
        LoginPacket login;
        login.deserialize_body(stream);
        this->username = login.username.C_String();
        this->x = SPAWN_X;
        this->y = SPAWN_Y;
        this->z = SPAWN_Z;

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
    } else if (packet_id == ReadyPacket::packet_id) {
        ReadyPacket ready_packet;
        ready_packet.deserialize_body(stream);
        if (ready_packet.status != 1) return;
        // Join game message
        printf("%s has joined the game\n", this->username.c_str());
        this->server->post_to_chat(this->username + " has joined!");
        // Add the player
        AddPlayerPacket add_player;
        add_player.client_guid = 0;
        add_player.username = this->username.c_str();
        add_player.entity_id = this->entity_id;
        add_player.x = this->x;
        add_player.y = this->y;
        add_player.z = this->z;
        add_player.pitch = this->pitch;
        add_player.yaw = this->yaw;
        this->broadcast_except_packet(add_player);
        // Add the other players
        std::map<const RakNet::RakNetGUID, RoadRunner::Player *>::iterator it = this->server->players.begin();
        while (it != this->server->players.end()) {
            if (it->first == this->guid) {
                ++it;
                continue;
            }
            Player *player = it->second;
            add_player.username = player->username.c_str();
            add_player.entity_id = player->entity_id;
            add_player.x = player->x;
            add_player.y = player->y;
            add_player.z = player->z;
            add_player.pitch = player->pitch;
            add_player.yaw = player->yaw;
            this->send_packet(add_player);
            ++it;
        }
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
        this->pitch = move_player.pitch;
        this->yaw = move_player.yaw;
    } else if (packet_id == RequestChunkPacket::packet_id) {
        RequestChunkPacket request_chunk;
        request_chunk.deserialize_body(stream);

        ChunkDataPacket chunk_data;
        chunk_data.x = request_chunk.x;
        chunk_data.z = request_chunk.z;
        chunk_data.chunk = new RoadRunner::world::Chunk(chunk_data.x, chunk_data.z);
        Perlin perlin;
        int32_t seed = 3;
        for (int32_t x = 0; x < 16; ++x) {
            for (int32_t z = 0; z < 16; ++z) {
                int32_t y = (int32_t)perlin.perlin(((chunk_data.x << 4) + x), ((chunk_data.z << 4) + z), 10.0 * (float)seed, 1, 8, 4, 0.4, 2) + 62;

                int32_t start_point = y;
                while (y >= 0) {
                    if (y < 1 && y >= 0) {
                        chunk_data.chunk->set_block_id(x, y, z, 7);
                    } else if (y < start_point && y > start_point - 4) {
                        if (y > 60) {
                            chunk_data.chunk->set_block_id(x, y, z, 3);
                        } else {
                            chunk_data.chunk->set_block_id(x, y, z, 13);
                        }
                    } else if (y == start_point) {
                        if (y > 61) {
                            chunk_data.chunk->set_block_id(x, y, z, 2);
                        } else {
                            chunk_data.chunk->set_block_id(x, y, z, 13);
                        }
                    } else {
                        chunk_data.chunk->set_block_id(x, y, z, 1);
                    }
                    --y;
                }
                for (int32_t i = 0; i < 62; ++i) {
                    if (chunk_data.chunk->get_block_id(x, i, z) == 0) {
                        chunk_data.chunk->set_block_id(x, i, z, 9);
                    }
                }
            }
        }
        this->send_packet(chunk_data);
    }
}
