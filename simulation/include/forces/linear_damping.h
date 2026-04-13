#pragma once
#include "force_field.h"

class LinearDamping : public ForceField {
    double factor;
public:
    explicit LinearDamping(double factor) : factor(factor) {}
    void apply(ParticleSystem2D& sys) override;
};
