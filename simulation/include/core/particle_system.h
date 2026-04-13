#pragma once
#include "particle.h"
#include "../forces/force_field.h"
#include "../collisions/collision_algo.h"
#include <vector>
#include <memory>

class integrator;   // forward — чтобы не тащить полный заголовок

class ParticleSystem2D {
    double time = 0.0;

public:
    double width;
    double height;
    std::vector<std::unique_ptr<ForceField>>    forces;
    std::vector<std::unique_ptr<CollisionAlgo>> collision_algos;
    std::vector<std::unique_ptr<particle>>      particles;

    explicit ParticleSystem2D(double right, double bottom);

    void add_force(std::unique_ptr<ForceField> f)         { forces.push_back(std::move(f)); }
    void add_collision_algo(std::unique_ptr<CollisionAlgo> a) { collision_algos.push_back(std::move(a)); }

    // Главный шаг: делегирует в интегратор
    void step(double dt, integrator& integ);

    // --- Вычисление сил (вызывается из интеграторов) ---
    void compute_forces();

    // --- Разрешение всех коллизий (вызывается из интеграторов) ---
    void resolve_all_collisions();

    // --- Управление частицами ---
    size_t add_particle(vec2 pos, vec2 vel, double mass,
                        double radius, const material& mat = materials::undefined);

    size_t add_random_particle();
    void   remove_particle(size_t id);

    // --- Утилиты ---
    void   show_particle_info(const particle& p) const;
    double get_time() const { return time; }
    size_t count() const { return particles.size(); }
};
