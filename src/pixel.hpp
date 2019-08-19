#ifndef INFERNO_PIXEL_H_
#define INFERNO_PIXEL_H_

#include <algorithm>

struct Pixel {
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Pixel(uint8_t r, uint8_t g, uint8_t b)
        : r(r), g(g), b(b) { };

    inline uint32_t argb() {
        return a << 24 | r << 16 | g << 8 | b;
    }

    inline uint32_t rgb() {
        return 0xFF000000 | r << 16 | g << 8 | b;
    }

    inline void Clamp() {
        std::max((uint8_t)0, std::min(a, (uint8_t)256));
        std::max((uint8_t)0, std::min(r, (uint8_t)256));
        std::max((uint8_t)0, std::min(g, (uint8_t)256));
        std::max((uint8_t)0, std::min(b, (uint8_t)256));
    }

};

inline uint8_t Clamp(int n, int upper, int lower) {
    return std::max(lower, std::min(n, upper));
}

inline uint32_t argb8888(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    return a << 24 | r << 16 | g << 8 | b;
}

inline uint32_t rgb888(uint8_t r, uint8_t g, uint8_t b) {
    return 0xFF000000 | r << 16 | g << 8 | b;
}

#endif
