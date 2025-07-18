#include "../../include/render/sfml_x.h"
#include "../../include/render/render_system.h"

std::unique_ptr<render_system>
render_system::init(const std::string &window_type,
                             const unsigned int width,
                             const unsigned int heights) {
    if (window_type == "SFML") {
        return sfml_window::create_window(width, heights);
    }
    return nullptr;
}
