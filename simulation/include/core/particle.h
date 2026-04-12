#pragma once
#include "../math/my_vector2.h"
#include "material.h"

class particle{
public:
    const double mass;
    vec2 force;
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    const material material_type;
    const double radius;

    particle(const vec2& initial_position, const vec2& initial_velocity, double particle_mass,  const vec2& force,
             const material& material_type = materials::undefined);
    particle(double w, double h);
};



class planet {};
