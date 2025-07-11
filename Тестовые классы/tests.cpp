//
// Created by Илья Чернов on 04.07.2025.
//

#include "particle.h"
#include <fstream>

int main() {

    std::ofstream File("heights.txt");
    if (!File) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return 1;
    }


    particle_system system(100);
    for (int i = 0; i < 100; ++i) {
        system.update(0.2);
        File << system.particles[0].position.y << '\n';
        system.render();
    }
    File.close();
    return 0;
}