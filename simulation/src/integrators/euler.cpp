#include "../../include/integrators/euler.h"
#include "../../include/core/particle_system.h"

void euler_integrator::step(ParticleSystem2D& sys, const double dt)
{
    sys.compute_forces();

    for (auto& p : sys.particles) {
        p->position     += p->velocity * dt + p->acceleration * (0.5 * dt * dt);
        p->velocity     += p->acceleration * dt;
        p->acceleration.reset();
    }

    sys.resolve_all_collisions();
}
