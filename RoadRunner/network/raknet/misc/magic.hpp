#pragma once

#include <cstdint>

class Magic {
public:
    static uint8_t magic[16];

    static bool validate_magic(uint8_t *magic_input);
};