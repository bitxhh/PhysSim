#include "../include/core/particle_system.h"
#include "../include/render/render_system.h"
#include <memory>
#include "../include/settings.h"


int main() {
    const std::unique_ptr<render_system> renderer = render_system::create("SFML", width, height);
    const auto system = std::make_unique<particle_system>
    (particle_system(100, renderer->width, renderer->heights));

    while (renderer->is_open()) {
        system->update(0.01);
        renderer->update(system->particles);
    }

    return 0;
}

