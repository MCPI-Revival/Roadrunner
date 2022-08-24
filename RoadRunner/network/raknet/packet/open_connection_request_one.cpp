#include <network/raknet/packet/open_connection_request_one.hpp>
#include <network/raknet/misc/magic.hpp>

bool OpenConnectionsRequestOne::deserialize_body() {
    uint8_t *magic;
    if (!this->read(16, &magic)) {
        return false;
    }
    if (!Magic::validate_magic(magic)) {
        return false;
    }
    if (!this->read_u8(&this->protocol_version)) {
        return false;
    }
    this->mtu_size = ((uint16_t) (this->size & 0xffff));
    if (this->mtu_size != 0xffff) {
        this->mtu_size += 28;
    }
    return true;
}

void OpenConnectionsRequestOne::serialize_body() {
    this->write(Magic::magic, 16);
    this->write_u8(this->protocol_version);
    size_t size = ((size_t) this->mtu_size) - 46;
    uint8_t *temp = (uint8_t *) calloc(size, 1);
    this->write(temp, size);
    free(temp);
}