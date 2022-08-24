#pragma once

#include <cstdint>
#include <iostream>

class InternetAddress {
public:
    std::string name;
    uint16_t port;
    uint8_t version;

    InternetAddress(std::string name, uint16_t port, uint8_t version);
};