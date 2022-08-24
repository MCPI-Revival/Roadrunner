#include <network/raknet/misc/internet_address.hpp>

InternetAddress::InternetAddress(std::string name, uint16_t port, uint8_t version) {
    this->name = name;
    this->port = port;
    this->version = version;
}