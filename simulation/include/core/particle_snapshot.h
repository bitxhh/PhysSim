#pragma once
#include "material.h"
#include "../math/my_vector2.h"

struct ParticleSnapshot {
    vec2   position;
    double radius;
    color3 color;
};
