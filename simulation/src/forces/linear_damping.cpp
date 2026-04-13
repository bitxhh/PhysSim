#include "../../include/forces/linear_damping.h"
#include "../../include/core/particle_system.h"

void LinearDamping::apply(ParticleSystem2D& sys)
{
    for (auto& p : sys.particles)
        p->velocity *= factor;
}
