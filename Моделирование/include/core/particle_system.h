#pragma once
#include "particle.h"
#include <fstream>

class particle_system {
    double time;
    size_t quantity;

public:
    std::vector<std::unique_ptr<particle>> particles;
    explicit particle_system(size_t particle_quantity);
    void simulate(double total_time, double dt);
    void update(double dt);
    void show_particle_info(const particle& p) const;
    void addGlobalForce();
    void addPairForce();
};