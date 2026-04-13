#pragma once
#include <cstdint>

struct color3 {
    uint8_t r, g, b;
    constexpr color3(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

struct material {
    const double density;
    const double friction;
    const double restitution;
    const color3 color;

    explicit material(double density, double friction = 1.0, double restitution = 1.0,
                      color3 color = {220, 220, 220})
        : density(density), friction(friction), restitution(restitution), color(color) {}
};

struct materials {
    inline static const auto Iron    = material(7.87, 0.15, 0.5,  {180, 180, 195});
    inline static const auto Glass   = material(2.5,  0.05, 0.9,  {180, 230, 255});
    inline static const auto Rubber  = material(1.1,  0.8,  0.6,  {220,  80,  80});
    inline static const auto undefined = material(0,  1.0,  1.0,  {220, 220, 220});
};
