#pragma once

#include <cstdint>

namespace RoadRunner {
    namespace world {
        class Perlin {
        public:
            uint32_t p[512];

            Perlin();

            float grad(int32_t hash, float x, float y, float z);

            float noise(float x, float y, float z);

            float perlin(float x, float y, float z, int32_t r, float scale, int32_t octaves, float persistence, float lacunarity);
        };
    }
}