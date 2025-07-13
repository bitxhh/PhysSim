//
// Created by Илья Чернов on 11.07.2025.
//

#ifndef ENGINE_H
#define ENGINE_H

namespace phisics {
    inline constexpr double g = 9.80665;
    inline constexpr double light_speed = 2.99792458e8;

    double potential_energy(double mass, double height);
    double kinetic_energy(double mass, double velocity);
    double energy(double mass, double height, double velocity);
    double rest_energy(double mass);
    double fall_velocity(double height);
}

#endif // ENGINE_H