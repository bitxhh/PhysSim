#include "../../include/core/particle_system.h"
#include "../../include/integrators/integrator.h"
#include <iomanip>

ParticleSystem2D::ParticleSystem2D(const double right, const double bottom)
    : width(right), height(bottom)
{}

// ──────────────────────────────────────────────────────────────
//  Главный шаг — делегирует в интегратор
// ──────────────────────────────────────────────────────────────
void ParticleSystem2D::step(const double dt, integrator& integ)
{
    integ.step(*this, dt);
    time += dt;
}

// ──────────────────────────────────────────────────────────────
//  Вычисление сил (вызывается из интеграторов)
// ──────────────────────────────────────────────────────────────
void ParticleSystem2D::compute_forces()
{
    for (auto& f : forces)
        f->apply(*this);
}

// ──────────────────────────────────────────────────────────────
//  Разрешение коллизий (вызывается из интеграторов)
// ──────────────────────────────────────────────────────────────
void ParticleSystem2D::resolve_all_collisions()
{
    for (auto& algo : collision_algos)
        algo->resolve(*this);
}

// ──────────────────────────────────────────────────────────────
//  Управление частицами
// ──────────────────────────────────────────────────────────────
size_t ParticleSystem2D::add_particle(vec2 pos, vec2 vel, double mass,
                                     double radius, const material& mat)
{
    particles.emplace_back(std::make_unique<particle>(pos, vel, mass, radius, mat));
    return particles.size() - 1;
}

size_t ParticleSystem2D::add_random_particle()
{
    particles.push_back(std::make_unique<particle>(width, height));
    return particles.size() - 1;
}

void ParticleSystem2D::remove_particle(size_t id)
{
    if (id >= particles.size()) return;
    particles[id].swap(particles.back());
    particles.pop_back();
}

void ParticleSystem2D::show_particle_info(const particle& p) const
{
    std::cout << std::fixed << std::setprecision(2)
              << "time: " << time << "   pos: " << p.position << '\n';
}
