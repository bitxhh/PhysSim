#include "../../include/scenarios/billiards.h"
#include "../../include/config.h"
#include "../../include/forces/linear_damping.h"
#include "../../include/collisions/box_constraint.h"
#include "../../include/collisions/brute_force_collision.h"
#include <cmath>

std::unique_ptr<ParticleSystem2D> billiards_scenario::create(const Config& cfg) const
{
    const unsigned W = preferred_width();
    const unsigned H = preferred_height();

    auto sys = std::make_unique<ParticleSystem2D>(
        static_cast<double>(W), static_cast<double>(H));

    sys->add_force(std::make_unique<LinearDamping>(0.9998));   // трение стола
    sys->add_collision_algo(std::make_unique<BoxConstraint>(W, H, cfg.minimal_radius));
    sys->add_collision_algo(std::make_unique<BruteForceCollision>(cfg.minimal_radius));

    // ── Материал шаров: упругий бильярдный шар ──
    const material ball_mat(1.6, 0.05, 0.96, {220, 220, 60});   // слоновая кость
    const material cue_mat (1.6, 0.05, 0.96, {245, 245, 245});  // белый кий-шар

    const double r       = 14.0;  // радиус шара
    const double spacing = r * 2.0 + 1.5;

    // Треугольник — 5 рядов, 15 шаров
    // Вершина треугольника обращена влево, открытая сторона вправо
    const double rack_x = W * 0.62;
    const double rack_y = H * 0.5;

    const double dx = spacing * std::sqrt(3.0) / 2.0;
    const double dy = spacing;

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col <= row; ++col) {
            const double x = rack_x + static_cast<double>(row) * dx;
            const double y = rack_y + (static_cast<double>(col) - row * 0.5) * dy;
            sys->add_particle({x, y}, {}, 1.0, r, ball_mat);
        }
    }

    // Кий-шар — удар вправо
    sys->add_particle({W * 0.25, H * 0.5}, {340.0, 0.0}, 1.0, r, cue_mat);

    return sys;
}
