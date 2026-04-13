#pragma once
#include "integrator.h"

// Явный метод Эйлера: x(t+dt) = x(t) + v(t)*dt + 0.5*a(t)*dt²
//                               v(t+dt) = v(t) + a(t)*dt
// Простой, быстрый, но плохо сохраняет энергию.
class euler_integrator final : public integrator {
public:
    void step(ParticleSystem2D& sys, double dt) override;
};
