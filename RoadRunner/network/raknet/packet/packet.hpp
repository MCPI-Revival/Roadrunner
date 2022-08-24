#pragma once

#include <binary_stream.hpp>
#include <network/raknet/misc/internet_address.hpp>
#include <iostream>

class Packet : public BinaryStream {
public:
    uint8_t packet_id;

    virtual bool deserialize_body() {
        return false;
    }

    virtual void serialize_body() {
    }

    bool deserialize();

    void serialize();

    bool read_string(std::string &string_value);

    void write_string(std::string &string_value);

    bool read_address(InternetAddress &internet_address);

    void write_address(InternetAddress &internet_address);
};