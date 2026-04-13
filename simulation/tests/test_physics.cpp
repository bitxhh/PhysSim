#include "../include/core/particle_system.h"
#include "../include/integrators/verlet.h"
#include "../include/collisions/box_constraint.h"
#include "../include/collisions/brute_force_collision.h"
#include "../include/forces/pair_gravity.h"
#include "../include/scenarios/billiards.h"
#include "../include/scenarios/solar_system.h"
#include "../include/config.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

static void check(bool cond, const char* msg)
{
    if (!cond) {
        std::cerr << "FAIL: " << msg << "\n";
        std::exit(1);
    }
}

// ── Тест 1: Бильярд — 100 шагов, количество шаров не меняется ─────────────
static void test_billiards_particle_count()
{
    const Config cfg;
    billiards_scenario scene;
    auto sys = scene.create(cfg);
    verlet_integrator integ;

    check(sys->count() == 16, "billiards: should start with 16 particles");

    for (int i = 0; i < 100; ++i)
        sys->step(scene.preferred_dt(), integ);

    check(sys->count() == 16, "billiards: particle count must stay 16 after 100 steps");
    std::cout << "PASS: billiards_particle_count\n";
}

// ── Тест 2: Солнечная система — сохранение энергии (Velocity Verlet) ───────
static double total_energy(const ParticleSystem2D& sys, double G)
{
    double ke = 0.0;
    for (const auto& p : sys.particles)
        ke += 0.5 * p->mass * (p->velocity * p->velocity);

    double pe = 0.0;
    for (size_t i = 0; i < sys.particles.size(); ++i)
        for (size_t j = i + 1; j < sys.particles.size(); ++j) {
            const vec2 d = sys.particles[j]->position - sys.particles[i]->position;
            const double r = std::sqrt(d * d);
            if (r > 1e-6)
                pe -= G * sys.particles[i]->mass * sys.particles[j]->mass / r;
        }
    return ke + pe;
}

static void test_solar_system_energy()
{
    const double G = 500.0;
    const Config cfg;
    solar_system_scenario scene;
    auto sys = scene.create(cfg);
    verlet_integrator integ;

    const double E0 = total_energy(*sys, G);

    for (int i = 0; i < 500; ++i)
        sys->step(scene.preferred_dt(), integ);

    const double E1    = total_energy(*sys, G);
    const double drift = std::abs((E1 - E0) / E0);

    check(drift < 0.01, "solar system: energy drift must be < 1% over 500 steps (Verlet)");
    std::cout << "PASS: solar_system_energy (drift=" << drift * 100.0 << "%)\n";
}

// ── Тест 3: Лобовое столкновение — сохранение импульса ────────────────────
static void test_momentum_conservation()
{
    const float min_r = 0.0f;
    auto sys = std::make_unique<ParticleSystem2D>(800.0, 600.0);
    sys->add_collision_algo(std::make_unique<BruteForceCollision>(min_r));

    // Полностью упругий материал (restitution = 1)
    const material mat(1.0, 0.0, 1.0, {255, 255, 255});
    const double r = 14.0;
    sys->add_particle({150.0, 300.0}, { 100.0, 0.0}, 1.0, r, mat);
    sys->add_particle({250.0, 300.0}, {-100.0, 0.0}, 1.0, r, mat);

    verlet_integrator integ;
    const double dt = 0.008;

    // Суммарный импульс до столкновения: (0, 0)
    const double px0 = sys->particles[0]->velocity.x + sys->particles[1]->velocity.x;
    const double py0 = sys->particles[0]->velocity.y + sys->particles[1]->velocity.y;

    for (int i = 0; i < 200; ++i)
        sys->step(dt, integ);

    const double px1 = sys->particles[0]->velocity.x + sys->particles[1]->velocity.x;
    const double py1 = sys->particles[0]->velocity.y + sys->particles[1]->velocity.y;

    const double err = std::abs(px1 - px0) + std::abs(py1 - py0);
    check(err < 1e-6, "head-on collision: total momentum must be conserved");
    std::cout << "PASS: momentum_conservation\n";
}

int main()
{
    test_billiards_particle_count();
    test_solar_system_energy();
    test_momentum_conservation();
    std::cout << "All tests passed.\n";
    return 0;
}
