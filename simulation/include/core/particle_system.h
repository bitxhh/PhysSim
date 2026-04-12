#pragma once
#include "particle.h"
#include <fstream>
#include <vector>
#include <memory>

class particle_system {
    double time;
    size_t quantity;
    double right_boundary;
    double bottom_boundary;

public:
    std::vector<std::unique_ptr<particle>> particles;
    explicit particle_system(size_t particle_quantity, double right, double bottom);

    //Симуляция
    void simulate(double total_time, double dt);
    void update(double dt);
    void update_parallel(double dt);

    //Утилиты
    void show_particle_info(const particle& p) const;
    void box_constraint(const std::unique_ptr<particle>&i) const;
    void addGlobalForce() const;
    void addPairForce() const;

    //Управление частицами
    auto add_random_particle() -> size_t;
    auto add_particle(vec2 pos, vec2 vel, double m, vec2 force = {}) -> size_t;
    void remove_particle(size_t id);
};