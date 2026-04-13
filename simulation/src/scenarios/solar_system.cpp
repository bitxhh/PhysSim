#include "../../include/scenarios/solar_system.h"
#include "../../include/config.h"
#include "../../include/forces/pair_gravity.h"
#include "../../include/collisions/box_constraint.h"
#include <cmath>

// ──────────────────────────────────────────────────────────────
// Масштаб "игровых единиц":
//   G_sim = 500,  M_sun = 1 000
//   Круговая орбита на радиусе r: v = sqrt(G_sim * M_sun / r)
// ──────────────────────────────────────────────────────────────
std::unique_ptr<ParticleSystem2D> solar_system_scenario::create(const Config& cfg) const
{
    const unsigned W = preferred_width();
    const unsigned H = preferred_height();

    auto sys = std::make_unique<ParticleSystem2D>(
        static_cast<double>(W), static_cast<double>(H));

    const double G_sim = 500.0;   // игровая единица
    sys->add_force(std::make_unique<PairGravity>(G_sim));
    sys->add_collision_algo(std::make_unique<BoxConstraint>(W, H, cfg.minimal_radius));

    const double cx = W / 2.0;
    const double cy = H / 2.0;
    const double M_sun = 1000.0;

    // ── Солнце ──
    const material sun_mat(0, 1, 1, {255, 220, 50});
    sys->add_particle({cx, cy}, {}, M_sun, 22.0, sun_mat);

    // ── Планеты: {радиус орбиты, масса, радиус шара, цвет} ──
    struct planet_def {
        double orbit_r;
        double mass;
        double radius;
        color3 color;
    };

    const planet_def planets[] = {
        { 80.0,  1.0,  5.0, {100, 140, 255}},  // "Меркурий" — синий
        {140.0,  1.0,  8.0, {220, 160,  60}},  // "Венера"   — оранжевый
        {210.0,  1.0,  9.0, { 60, 160, 255}},  // "Земля"    — голубой
        {290.0,  1.0, 12.0, {200,  90,  60}},  // "Марс"     — красный
    };

    for (const auto& pd : planets) {
        const double v_circ = std::sqrt(G_sim * M_sun / pd.orbit_r);
        // Стартуем справа от Солнца, скорость направлена вверх (против часовой)
        const vec2 pos = {cx + pd.orbit_r, cy};
        const vec2 vel = {0.0, v_circ};

        const material mat(pd.mass, 1.0, 0.8, pd.color);
        sys->add_particle(pos, vel, pd.mass, pd.radius, mat);
    }

    // ── Импульс системы: компенсируем скорость Солнца ──
    // Суммарный импульс планет направлен вверх, даём Солнцу противоположный.
    double total_p = 0.0;
    for (size_t i = 1; i < sys->particles.size(); ++i)
        total_p += sys->particles[i]->mass * sys->particles[i]->velocity.y;
    sys->particles[0]->velocity.y = -total_p / M_sun;

    return sys;
}
