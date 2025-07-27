#include "../../include/core/particle_system.h"
#include <iomanip>
#include "../../include/math/phisics.h"
#include "../../include/core/material.h"
#include "../../include/settings.h"

particle_system::particle_system(const size_t particle_quantity, const double right, const double bottom)
    : time(0), quantity(particle_quantity), right_boundary(right), bottom_boundary(bottom) {
    for (int i = 0; i < particle_quantity; ++i) {
        add_random_particle();
    }
    quantity -= particle_quantity;
}

void particle_system::simulate(const double total_time, const double dt) {
    while (time < total_time) {
        update(dt);
    }
}

void particle_system::box_constraint(const std::unique_ptr<particle>&i) const {
    if (i->position.y > bottom_boundary-(i->radius+minimal_radius)) {
        i->position.y = bottom_boundary-(i->radius+minimal_radius);
        i->velocity.y = -i->velocity.y * i->material_type.restitution;
    }
    if (i->position.x > right_boundary-(i->radius+minimal_radius)) {
        i->position.x = right_boundary-(i->radius+minimal_radius);
        i->velocity.x = -i->velocity.x * i->material_type.restitution;
    }
    if (i->position.y < i->radius+minimal_radius) {
        i->position.y = i->radius+minimal_radius;
        i->velocity.y = -i->velocity.y * i->material_type.restitution;
    }
    if (i->position.x < i->radius+minimal_radius) {
        i->position.x = i->radius+minimal_radius;
        i->velocity.x = -i->velocity.x * i->material_type.restitution;
    }
}

void particle_system::addGlobalForce() const {
    for (const std::unique_ptr<particle>&i: particles) {
        i->acceleration += phisics::g;
    }
}

void particle_system::addPairForce() const {
    for (const std::unique_ptr<particle>&i: particles) {
        for (const std::unique_ptr<particle>&j: particles) {
            if (i.get() == j.get()) continue;

            vec2 r_vec = j->position - i->position;
            const double distance_squared = r_vec.x * r_vec.x + r_vec.y * r_vec.y;
            if (distance_squared > 1e-12) {
                i->force += r_vec.normalized() * (
                    (phisics::G * i->mass * j->mass) /
                    distance_squared);
            }
        }
        i->acceleration += i->force / i->mass;
        i->force.reset();
    }
}

void particle_system::update(const double dt) {
    addPairForce();
    addGlobalForce();

    for (const std::unique_ptr<particle>&i: particles) {
        i->position += i->velocity * dt + i->acceleration * dt * dt * 0.5;
        i->velocity += i->acceleration * dt;

        box_constraint(i);

        i->acceleration.reset();
    }
    time += dt;
}

void particle_system::update_parallel(const double dt)
{
    // TODO: реализовать параллельный апдейт.
    // Сейчас просто перенаправляем на последовательный вариант,
    // чтобы вызывающий код уже мог пользоваться этим методом.
    update(dt);
}


void particle_system::show_particle_info(const particle &p) const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "time: " << time << "   " << "pos: " << p.position << std::endl;
}



size_t particle_system::add_particle(vec2 pos, vec2 vel,
                                     double m, vec2 force)
{
    particles.emplace_back(std::make_unique<particle>(pos,vel,m,force));
    ++quantity;
    return particles.size()-1;
}

size_t particle_system::add_random_particle()
{
    particles.push_back(std::make_unique<particle>(width, height));
    ++quantity;
    return particles.size()-1;
}

void particle_system::remove_particle(size_t id)
{
    if(id>=particles.size()) return;            // safety
    particles[id].swap(particles.back());
    particles.pop_back();
    --quantity;
}

