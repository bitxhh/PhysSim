#pragma once

struct material {
    const double density;
    const double friction;
    const double restitution;
    explicit material(const double density, const double friction = 1, const double restitution = 0.5)
        : density(density), friction(friction), restitution(restitution) {}
};

struct materials {
    inline static const auto Iron   = material(7.87, 0.15);
    inline static const auto Glass  = material(2.5, 0.05);
    inline static const auto Rubber = material(1.1, 0.8);
    inline static const auto undefined  = material(0, 1);
};