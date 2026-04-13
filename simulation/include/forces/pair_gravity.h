#pragma once
#include "force_field.h"

class PairGravity : public ForceField {
    double G;
public:
    explicit PairGravity(double gravitational_constant) : G(gravitational_constant) {}
    void apply(ParticleSystem2D& sys) override;
};
