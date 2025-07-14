#pragma once

#include <SFML/Window.hpp>

class sfml_window {
public:
    sf::Window window;
    unsigned int heights;
    unsigned int width;

    sfml_window(const unsigned int heights, const unsigned int width) : window((sf::VideoMode({heights, width})), "Simulation"), heights(heights), width(width) {
        window.setVerticalSyncEnabled(true);
    }

    void check_for_events() {
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }
};
