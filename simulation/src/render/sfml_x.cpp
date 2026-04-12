#include "../../include/render/sfml_x.h"
#include <SFML/Graphics.hpp>
#include "../../include/render/render_system.h"
#include <memory>
#include "../../include/settings.h"


void sfml_window::check_for_events() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
        }
    }

void sfml_window::draw(const particle& p)
{
    /* 1. Радиус хранится в double — нужно привести к float */
    const auto radius = static_cast<float>(p.radius) + minimal_radius;

    sf::CircleShape circle(radius);

    /* 2. Центр фигуры совмещаем с геометрическим центром,
          чтобы setPosition ставил именно ЦЕНТР круга          */
    circle.setOrigin(sf::Vector2f{radius, radius});

    /* 3. Преобразуем ваш vec2 → sf::Vector2f */
    const sf::Vector2f pos{
        static_cast<float>(p.position.x),
        static_cast<float>(p.position.y)
    };
    circle.setPosition(pos);

    circle.setFillColor(sf::Color::White);

    window.draw(circle);
}

sfml_window::sfml_window(const unsigned int width, const unsigned int height)
    : render_system(width, height),
      window((sf::VideoMode({width, height})), "Simulation") {
    window.setVerticalSyncEnabled(true);
    // ---Преобразование координат---------------------------------
    sf::View view(sf::FloatRect({0.f, 0.f},
                                {static_cast<float>(width),
                                static_cast<float>(height)}));

    view.setCenter({static_cast<float>(width)  / 2.f,
                   static_cast<float>(height) / 2.f});
    view.setSize ({static_cast<float>(width),  -static_cast<float>(height)});

    window.setView(view);
    // ---------------------------------------------------------

}

std::unique_ptr<render_system> sfml_window::create_window(const unsigned int width,
                                                          const unsigned int height) {
    return std::make_unique<sfml_window>(width, height);
}

[[nodiscard]] bool sfml_window::is_open() const
{
    return window.isOpen();
}

void sfml_window::update(const std::vector<std::unique_ptr<particle>>& particles)
{
    check_for_events();
    window.clear();

    for (const auto& p : particles)
        draw(*p);

    window.display();
}

