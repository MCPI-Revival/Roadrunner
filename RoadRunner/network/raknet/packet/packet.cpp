#include <cstdlib>
#include <cstring>
#include <network/raknet/packet/packet.hpp>
#ifdef _WIN32
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

bool Packet::deserialize() {
    if (!this->read_u8(&this->packet_id)) {
        return false;
    }
    return this->deserialize_body();
}

void Packet::serialize() {
    this->write_u8(this->packet_id);
    this->serialize_body();
}

bool Packet::read_string(std::string &string_value) {
    uint16_t length;
    uint8_t *out;
    if (!this->read_u16be(&length)) {
        return false;
    }
    if (!this->read(length, &out)) {
        return false;
    }
    std::string temp_string((char *)out);
    string_value = temp_string;
    return true;
}

void Packet::write_string(std::string &string_value) {
    this->write_u16be(string_value.length());
    this->write((uint8_t *)string_value.c_str(), string_value.length());
}

bool Packet::read_address(InternetAddress &internet_address) {
    if (!this->read_u8(&internet_address.version)) {
        return false;
    }
    if (internet_address.version == 4) {
        uint8_t *parts;
        if (!this->read(4, &parts)) {
            return false;
        }
        *((uint32_t *)parts) = ~(*((uint32_t *)parts));
        char buf[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, parts, buf, INET_ADDRSTRLEN);
        std::string name(buf);
        internet_address.name = name;
        if (!this->read_u16be(&internet_address.port)) {
            return false;
        }
        return true;
    } else if (internet_address.version == 6) {
        uint8_t *temp;
        if (!this->read(2, &temp)) {
            return false;
        }
        if (!this->read_u16be(&internet_address.port)) {
            return false;
        }
        if (!this->read(4, &temp)) {
            return false;
        }
        uint8_t *parts;
        if (!this->read(16, &parts)) {
            return false;
        }
        char buf[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, parts, buf, INET6_ADDRSTRLEN);
        std::string name(buf);
        internet_address.name = name;
        if (!this->read(4, &temp)) {
            return false;
        }
        return true;
    }
    return false;
}

void Packet::write_address(InternetAddress &internet_address) {
    this->write_u8(internet_address.version);
    if (internet_address.version == 4) {
        uint8_t parts[4];
        inet_pton(AF_INET, internet_address.name.c_str(), parts);
        *((uint32_t *)parts) = ~(*((uint32_t *)parts));
        this->write(parts, 4);
        this->write_u16be(internet_address.port);
    } else if (internet_address.version == 6) {
        this->write_u16le(AF_INET6);
        this->write_u16be(internet_address.port);
        this->write_u32be(0);
        uint8_t parts[16];
        inet_pton(AF_INET6, internet_address.name.c_str(), parts);
        this->write(parts, 16);
        this->write_u32be(0);
    }
}