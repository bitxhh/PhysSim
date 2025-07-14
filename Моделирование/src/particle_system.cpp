#include "../include/particle_system.h"
#include <iomanip>
#include "../include/math/phisics.h"

particle_system::particle_system(const size_t particle_quantity)
    : time(0), quantity(particle_quantity), window(sfml_window(800, 600)) {
    particles.emplace_back(vec2(0, 100), vec2(0, 0), 10);
    particles.emplace_back(vec2(0.01, 100), vec2(0, 0), 0.01);
}

void particle_system::simulate (const double total_time, const double dt) {
    while (window.window.isOpen()) {
        while (time < total_time){
            update(dt);
            show_particle_info(particles[0]);
        }
        render();
    }
}

void particle_system::update(const double dt) {

    for (particle& i:particles) {
        vec2 force(0, 0);
        for (const particle& j:particles) {
            if (&i == &j) continue;

            vec2 r_vec = j.position - i.position;
            const double distance_squared = r_vec.x * r_vec.x + r_vec.y * r_vec.y;
            if (distance_squared > 1e-12) {
                force += r_vec.normalized() * (
                    (phisics::G * i.mass * j.mass) /
                    distance_squared);
            }
        }
        i.acceleration = force / i.mass + phisics::g;
    }


    for (particle& i:particles) {

        i.position += i.velocity * dt + i.acceleration * dt * dt * 0.5;
        i.velocity += i.acceleration * dt;


        if (i.position.y < 0) {
            i.position.y = 0;
            i.velocity.y = -i.velocity.y * i.material_type.restitution;
        }
    }
    render();
    time += dt;
}

void particle_system::render() {
    window.check_for_events();
}
void particle_system::show_particle_info(const particle& p) const{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "time: " << time << "   " << "pos: " << p.position << std::endl;
}

