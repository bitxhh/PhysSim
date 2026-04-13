#include "../../include/core/particle.h"
#include "../../include/math/physics.h"
#include <stdexcept>
#include <cmath>
#include <random>

particle::particle(const vec2& pos, const vec2& vel,
                   const double particle_mass, const double explicit_radius,
                   const material& mat)
    : mass(particle_mass),
      position(pos),
      velocity(vel),
      acceleration(),
      prev_acceleration(),
      material_type(mat),
      radius(explicit_radius)
{
    if (mass <= 0)
        throw std::invalid_argument("mass can't be negative or zero");
    if (explicit_radius < 0)
        throw std::invalid_argument("radius can't be negative");
}

particle::particle(double w, double h)
    /* ------------------- генераторы и распределения ------------------- */
    : mass([]{
          static thread_local std::mt19937 rng{std::random_device{}()};
          static std::uniform_real_distribution<double> m_d(0.1, 10.0);
          return m_d(rng);
      }()),
      position([&]{
          static thread_local std::mt19937 rng{std::random_device{}()};
          std::uniform_real_distribution<double> dx(0.0, w);
          std::uniform_real_distribution<double> dy(0.0, h);
          return vec2{dx(rng), dy(rng)};
      }()),
      velocity([]{
          static thread_local std::mt19937 rng{std::random_device{}()};
          static std::normal_distribution<double> v_d(0.0, 1.0);
          return vec2{v_d(rng), v_d(rng)};
      }()),
      acceleration(),
      prev_acceleration(),
      material_type([]{
          static thread_local std::mt19937 rng{std::random_device{}()};
          static std::discrete_distribution<size_t> choose{1, 3, 1}; // веса
          static const material variants[] = {
              materials::undefined,
              materials::Iron,
              materials::Rubber
          };
          return variants[choose(rng)];
      }()),
      radius((material_type.density != 0)
             ? cbrt(3 * mass / (4 * physics::pi * material_type.density))
             : 0.0)
{
    if (mass <= 0.0)
        throw std::invalid_argument("mass can't be negative or zero");
}
