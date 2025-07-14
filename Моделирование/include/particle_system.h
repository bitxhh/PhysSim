#pragma once
#include "../include/particle.h"
#include <fstream>
#include "../include/visualize.h"

class particle_system {
    double time;
    size_t quantity;
    sfml_window window;

public:
    std::vector<particle> particles;
    explicit particle_system(size_t particle_quantity);
    void simulate(double total_time, double dt);
    void update(double dt);
    void render ();
    void show_particle_info(const particle& p) const;
};