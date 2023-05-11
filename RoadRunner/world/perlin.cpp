#include <world/perlin.hpp>
#include <cmath>

static float perlin_gradient_vectors[16][3] = {
    // Standard vectors
    {1, 1, 0},
    {-1, 1, 0},
    {1, -1, 0},
    {-1, -1, 0},
    {1, 0, 1},
    {-1, 0, 1},
    {1, 0, -1},
    {-1, 0, -1},
    {0, 1, 1},
    {0, -1, 1},
    {0, 1, -1},
    {0, -1, -1},
    // Performance vectors
    {1, 1, 0},
    {-1, 1, 0},
    {0, -1, 1},
    {0, -1, -1},
};

static uint32_t perlin_permutation[512] = {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87,
    174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89,
    18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152,
    2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
    49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
};

static float perlins[14][2] = {
    {0.0625, 16},
    {0.0625, 16},
    {0.05, 20},
    {0.05, 20},
    {0.045454545454545456, 22},
    {0.045454545454545456, 22},
    {0.03225806451612903, 31},
    {0.03225806451612903, 31},
    {0.03125, 32},
    {0.03125, 32},
    {0.015625, 64},
    {0.015625, 64},
    {0.001953125, 512},
    {0.001953125, 512},
};

static float avg = 0.08031678768442099;

#define FADE(t) (6 * t * t * t * t * t - 15 * t * t * t * t + 10 * t * t * t)
#define LERP(v0, v1, t) (v0 + t * (v1 - v0))
#define DOT(ax, bx, ay, by, az, bz) (ax * bx + ay * by + az * bz)
#define GRAD(hash, x, y, z) (DOT( \
    perlin_gradient_vectors[hash & 0x0f][0], \
    perlin_gradient_vectors[hash & 0x0f][1], \
    perlin_gradient_vectors[hash & 0x0f][2], \
    x, y, z \
))

RoadRunner::world::Perlin::Perlin() {
    for (uint32_t x = 0; x < 512; ++x) {
        this->p[x] = perlin_permutation[x % 256];
    }
}

float RoadRunner::world::Perlin::noise(float x, float y, float z) {
    uint32_t xi = (uint32_t)floorf(x) & 255;
    uint32_t yi = (uint32_t)floorf(y) & 255;
    uint32_t zi = (uint32_t)floorf(z) & 255;
    float xf = x - floorf(x);
    float yf = y - floorf(y);
    float zf = z - floorf(z);

    uint32_t aaa = this->p[this->p[this->p[xi] + yi] + zi];
    uint32_t aba = this->p[this->p[this->p[xi] + yi + 1] + zi];
    uint32_t aab = this->p[this->p[this->p[xi] + yi] + zi + 1];
    uint32_t abb = this->p[this->p[this->p[xi] + yi + 1] + zi + 1];
    uint32_t baa = this->p[this->p[this->p[xi + 1] + yi] + zi];
    uint32_t bba = this->p[this->p[this->p[xi + 1] + yi + 1] + zi];
    uint32_t bab = this->p[this->p[this->p[xi + 1] + yi] + zi + 1];
    uint32_t bbb = this->p[this->p[this->p[xi + 1] + yi + 1] + zi + 1];

    float u = FADE(xf);
    float v = FADE(yf);
    float w = FADE(zf);

    float x1 = LERP(GRAD(aaa, xf, yf, zf), GRAD(baa, xf - 1, yf, zf), u);
    float x2 = LERP(GRAD(aba, xf, yf - 1, zf), GRAD(bba, xf - 1, yf - 1, zf), u);
    float y1 = LERP(x1, x2, v);
    x1 = LERP(GRAD(aab, xf, yf, zf - 1), GRAD(bab, xf - 1, yf, zf - 1), u);
    x2 = LERP(GRAD(abb, xf, yf - 1, zf - 1), GRAD(bbb, xf - 1, yf - 1, zf - 1), u);
    float y2 = LERP(x1, x2, v);

    return LERP(y1, y2, w);
}

float RoadRunner::world::Perlin::perlin(float x, float y, float z, uint32_t r, float scale, uint32_t octaves, float persistence, float lacunarity) {
    float frequency = 1;
    float amplitude = 1;
    float height = 0;

    for (uint32_t i = 0; i < octaves; ++i) {
        float sample_x = (x / scale) * frequency * ((float)i + 1);
        float sample_y = (y / scale) * frequency * ((float)i + 1);
        float sample_z = (z / scale) * frequency * ((float)i + 1);
        float total = 0;
        for (uint32_t j = 0; j < 14; ++j) {
            float s = perlins[j][0];
            float h = perlins[j][1];
            total += this->noise(sample_x * s, sample_y * s, sample_z * s) * amplitude * h;
        }
        total *= (avg * 1) / ((float)i + 1);
        height += total;

        amplitude *= persistence;
        frequency *= lacunarity;
    }
    return height;
}