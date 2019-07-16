#ifndef INFERNO_PIXEL_H_
#define INFERNO_PIXEL_H_

struct Pixel {
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;

    inline uint32_t argb() {
        return a << 24 | r << 16 | g << 8| b;
    }

    inline uint32_t rgb() {
        return 0xFF000000 | r << 16 | g << 8| b;
    }
};


inline uint32_t argb8888(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    return a << 24 | r << 16 | g << 8| b;
}

inline uint32_t rgb888(uint8_t r, uint8_t g, uint8_t b) {
    return 0xFF000000 | r << 16 | g << 8| b;
}

#endif
