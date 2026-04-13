#include "../../include/integrators/verlet.h"
#include "../../include/core/particle_system.h"

void verlet_integrator::step(ParticleSystem2D& sys, const double dt)
{
    // ── Шаг 1: обновляем позиции, запоминаем старые ускорения ──
    for (auto& p : sys.particles) {
        p->position         += p->velocity * dt + p->acceleration * (0.5 * dt * dt);
        p->prev_acceleration = p->acceleration;
        p->acceleration.reset();
    }

    // ── Шаг 2: вычисляем силы в новых позициях ──
    sys.compute_forces();

    // ── Шаг 3: обновляем скорости средним ускорений ──
    // Не сбрасываем acceleration — оно понадобится в шаге 1 следующего вызова
    for (auto& p : sys.particles)
        p->velocity += (p->prev_acceleration + p->acceleration) * (0.5 * dt);

    sys.resolve_all_collisions();
}
