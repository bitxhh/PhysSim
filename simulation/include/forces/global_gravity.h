#pragma once
#include "force_field.h"
#include "../math/my_vector2.h"
#include "../math/physics.h"

class GlobalGravity : public ForceField {
    vec2 g;
public:
    explicit GlobalGravity(vec2 gravity = physics::g) : g(gravity) {}
    void apply(ParticleSystem2D& sys) override;
};
