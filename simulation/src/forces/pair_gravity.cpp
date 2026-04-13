#include "../../include/forces/pair_gravity.h"
#include "../../include/core/particle_system.h"
#include <cmath>

void PairGravity::apply(ParticleSystem2D& sys)
{
    for (size_t i = 0; i < sys.particles.size(); ++i) {
        for (size_t j = i + 1; j < sys.particles.size(); ++j) {
            auto& a = *sys.particles[i];
            auto& b = *sys.particles[j];

            vec2 r_vec = b.position - a.position;
            const double dist2 = r_vec.x * r_vec.x + r_vec.y * r_vec.y;
            if (dist2 < 1e-6) continue;

            const double dist      = std::sqrt(dist2);
            const double force_mag = G * a.mass * b.mass / dist2;
            const vec2   force_dir = r_vec / dist;

            a.acceleration += force_dir * (force_mag / a.mass);
            b.acceleration -= force_dir * (force_mag / b.mass);
        }
    }
}
