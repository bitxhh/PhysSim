//
// Created by Илья Чернов on 04.07.2025.
//

#include "../include/particle_system.h"

int main() {
    particle_system system(100);
    system.simulate(20, 1);

    return 0;
}