#include "../../include/collisions/brute_force_collision.h"
#include "../../include/core/particle_system.h"
#include <cmath>
#include <algorithm>

void BruteForceCollision::resolve(ParticleSystem2D& sys)
{
    for (size_t i = 0; i < sys.particles.size(); ++i) {
        for (size_t j = i + 1; j < sys.particles.size(); ++j) {
            particle& a = *sys.particles[i];
            particle& b = *sys.particles[j];

            const vec2   delta  = b.position - a.position;
            const double dist2  = delta.x * delta.x + delta.y * delta.y;
            const double min_d  = a.radius + b.radius + 2.0 * min_r;

            if (dist2 >= min_d * min_d || dist2 < 1e-12) continue;

            const double dist    = std::sqrt(dist2);
            const vec2   normal  = delta / dist;
            const double overlap = min_d - dist;

            const double inv_total = 1.0 / (a.mass + b.mass);
            a.position -= normal * (overlap * b.mass * inv_total);
            b.position += normal * (overlap * a.mass * inv_total);

            const vec2   rel_vel = a.velocity - b.velocity;
            const double vel_n   = rel_vel * normal;
            if (vel_n >= 0.0) continue;

            const double e     = std::min(a.material_type.restitution,
                                          b.material_type.restitution);
            const double j_imp = -(1.0 + e) * vel_n /
                                   (1.0 / a.mass + 1.0 / b.mass);

            const vec2 impulse = normal * j_imp;
            a.velocity += impulse / a.mass;
            b.velocity -= impulse / b.mass;
        }
    }
}
