#pragma once
#include "particle.h"
#include <fstream>

class particle_system {
    double time;
    size_t quantity;
    double right_boundary;
    double bottom_boundary;

public:
    std::vector<std::unique_ptr<particle>> particles;
    explicit particle_system(size_t particle_quantity, double right, double bottom);
    void simulate(double total_time, double dt);
    void update(double dt);
    void show_particle_info(const particle& p) const;
    void box_constraint(const std::unique_ptr<particle>&i) const;
    void addGlobalForce() const;
    void addPairForce() const;
};