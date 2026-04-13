#include "../../include/collisions/box_constraint.h"
#include "../../include/core/particle_system.h"

void BoxConstraint::resolve(ParticleSystem2D& sys)
{
    for (auto& p : sys.particles) {
        const double r = p->radius + min_r;

        if (p->position.y > bottom - r) {
            p->position.y = bottom - r;
            p->velocity.y = -p->velocity.y * p->material_type.restitution;
        }
        if (p->position.y < r) {
            p->position.y = r;
            p->velocity.y = -p->velocity.y * p->material_type.restitution;
        }
        if (p->position.x > right - r) {
            p->position.x = right - r;
            p->velocity.x = -p->velocity.x * p->material_type.restitution;
        }
        if (p->position.x < r) {
            p->position.x = r;
            p->velocity.x = -p->velocity.x * p->material_type.restitution;
        }
    }
}
