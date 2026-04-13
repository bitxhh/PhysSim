#pragma once
#include "../math/my_vector2.h"
#include "material.h"

class particle {
public:
    const double mass;
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    vec2 prev_acceleration;   // используется Velocity Verlet
    const material material_type;
    const double radius;

    // Конструктор с явным радиусом — для сценариев (бильярд, планеты)
    particle(const vec2& pos, const vec2& vel, double mass,
             double radius, const material& mat = materials::undefined);

    // Случайная частица в границах экрана
    explicit particle(double w, double h);
};
