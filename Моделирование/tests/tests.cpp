#include "../include/particle_system.h"

int main() {
    particle_system system(100);
    for (double i = 0; i<20;) {
        system.update(0.01);
        system.show_particle_info(system.particles[0]);
        i += 0.01;
    }

    return 0;
}