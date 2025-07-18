//
// Created by Илья Чернов on 04.07.2025.
//

#include "../../include/core/particle.h"
#include <stdexcept>
#include <cmath>
#include "../../include/math/phisics.h"


particle::particle(const vec2& initial_position,
                   const vec2& initial_velocity,
                   const double particle_mass,
                   const vec2& force,
                   const material& material_type):

    mass(particle_mass),
    force(force),
    position(initial_position),
    velocity(initial_velocity),
    acceleration(0,0),
    radius((material_type.density != 0)
    ? cbrt(3 * particle_mass / (4 * phisics::pi * material_type.density))
    : 0),

    material_type(material_type) {
    if (mass <= 0) {
        throw std::invalid_argument("mass can't be negative or zero");
    }
}