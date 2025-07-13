#pragma once
#include "math/my_vector2.h"
#include "material.h"

class particle {
public:
    const double mass;
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    const double radius;
    const material material_type;

    particle(const vec2& initial_position, const vec2& initial_velocity, double particle_mass,
        const material& material_type = materials::undefined);
};
