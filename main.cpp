#include <iostream>
#include "Engine.cpp"
#include <iomanip>

int main() {
    double electron_rest_energy = phisics::rest_energy(9.1e-31);
    double car_kinetic_energy = phisics::kinetic_energy(1500, 25);
    double height;
    std::cout << "Демонстрация работы namespace \n";
    std::cout << std::scientific << std::setprecision(2);
    std::cout << "1. Расчёт энергии покоя электрона m = 9.1e-31 кг" << "\n";
    std::cout << "Энергия покоя электрона: " << electron_rest_energy << " J" << "\n";
    std::cout << "\n" << "2. Рассчёт кинетической энергии автомобиля m = 1500 кг, v = 25 м/с" << "\n";
    std::cout << "Кинетическая энергия автомобиля: " << car_kinetic_energy << " J" << "\n";
    std::cout << "\n" << "3. Скорость свободного падения с высоты : ";
    std::cin >> height;
    double fall_velocity = phisics::fall_velocity(height);
    std::cout << "v = " << fall_velocity << "m/c";
    std::cout << "\n" << "v = " << fall_velocity * 3.6 << " km/h";
    std::cout << "\n" << "Время падения: " << fall_velocity/phisics::g;


    return 0;
}