#pragma once

#include <cstdint>

namespace RoadRunner {
    namespace world {
        class Perlin {
        public:
            uint32_t p[512];

            Perlin();

            float noise(float x, float y, float z);

            float perlin(float x, float y, float z, uint32_t r, float scale, uint32_t octaves, float persistence, float lacunarity);
        };
    }
}