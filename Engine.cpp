namespace phisics {
    constexpr double g = 9.80665;
    constexpr double light_speed = 2.99792458e8;

    double potential_energy(double mass, double height) {
        return mass * g * height;
    }
    double kinetic_energy(double mass, double velocity) {
        return 0.5 * mass * velocity * velocity;
    }
    double energy(double mass, double height, double velocity) {
        return potential_energy(mass, height) + kinetic_energy(mass, velocity);
    }
    double rest_energy(double mass) {
        return mass * light_speed * light_speed;
    }
    double fall_velocity(double height) {
        return std::sqrt(2 * g * height);
    }
}
