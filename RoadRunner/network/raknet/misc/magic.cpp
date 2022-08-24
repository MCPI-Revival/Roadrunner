#include <network/raknet/misc/magic.hpp>

uint8_t Magic::magic[16] = {
    0x00, 0xff, 0xff, 0x00,
    0xfe, 0xfe, 0xfe, 0xfe,
    0xfd, 0xfd, 0xfd, 0xfd,
    0x12, 0x34, 0x56, 0x78};

bool Magic::validate_magic(uint8_t *magic_input) {
    for (uint8_t i = 0; i < 16; ++i) {
        if (Magic::magic[i] != magic_input[i]) {
            return false;
        }
    }
    return true;
}