#pragma once
#include "integrator.h"

// Velocity Verlet: симплектический интегратор 2-го порядка.
// Два вычисления сил за шаг — точнее сохраняет энергию,
// особенно важно для орбитальной механики и упругих столкновений.
//
//  1) x(t+dt) = x(t) + v(t)*dt + 0.5*a(t)*dt²
//  2) a(t+dt) = F(x(t+dt)) / m
//  3) v(t+dt) = v(t) + 0.5*(a(t) + a(t+dt))*dt
class verlet_integrator final : public integrator {
public:
    void step(ParticleSystem2D& sys, double dt) override;
};
