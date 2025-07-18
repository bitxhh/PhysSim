#pragma once

#include <SFML/Graphics.hpp>
#include "render_system.h"
#include <memory>

class sfml_window final : public render_system{
    sf::RenderWindow window;

    void check_for_events() override {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }

    void draw(const particle& p) override
    {
        /* 1. Радиус хранится в double — нужно привести к float */

        sf::CircleShape circle(25);

        /* 2. Центр фигуры совмещаем с геометрическим центром,
              чтобы setPosition ставил именно ЦЕНТР круга          */
        circle.setOrigin(sf::Vector2f{25, 25});

        /* 3. Преобразуем ваш vec2 → sf::Vector2f */
        const sf::Vector2f pos{
            static_cast<float>(p.position.x),
            static_cast<float>(p.position.y)
        };
        circle.setPosition(pos);

        circle.setFillColor(sf::Color::White);

        window.draw(circle);
    }

public:
    explicit sfml_window(const unsigned int width, const unsigned int heights)
        : render_system(width, heights),
          window((sf::VideoMode({heights, width})), "Simulation") {
        window.setVerticalSyncEnabled(true);
    }

    static std::unique_ptr<render_system>
    create_window(const unsigned int width, const unsigned int heights) {
        return std::make_unique<sfml_window>(width, heights);
    }

    [[nodiscard]] bool is_open() const override
    {
        return window.isOpen();
    }

    void update(const std::vector<std::unique_ptr<particle>>& particles) override
    {
        check_for_events();
        window.clear();

        for (const auto& p : particles)
            draw(*p);

        window.display();
    }

    ~sfml_window() override = default;
};
