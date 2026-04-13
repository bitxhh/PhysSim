#include "../../include/forces/global_gravity.h"
#include "../../include/core/particle_system.h"

void GlobalGravity::apply(ParticleSystem2D& sys)
{
    for (auto& p : sys.particles)
        p->acceleration += g;
}
