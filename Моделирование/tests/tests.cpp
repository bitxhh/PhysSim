#include "../include/core/particle_system.h"
#include "../include/render/render_system.h"
#include <memory>


int main() {
    particle_system system(100);
    const std::unique_ptr<render_system> renderer = render_system::init("SFML", 1000, 1000);

    while (renderer->is_open()) {
        system.update(0.01);
        renderer->update(system.particles);
    }

    return 0;
}
