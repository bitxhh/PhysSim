#pragma once

class ParticleSystem2D;

class ForceField {
public:
    virtual void apply(ParticleSystem2D& sys) = 0;
    virtual ~ForceField() = default;
};
