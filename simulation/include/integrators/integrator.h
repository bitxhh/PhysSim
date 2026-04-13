#pragma once

class ParticleSystem2D;

class integrator {
public:
    virtual void step(ParticleSystem2D& sys, double dt) = 0;
    virtual ~integrator() = default;
};
