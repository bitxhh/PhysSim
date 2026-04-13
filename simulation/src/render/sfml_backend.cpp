#include "../../include/render/sfml_backend.h"

SFMLBackend::SFMLBackend(const unsigned width, const unsigned height, const float min_r)
    : window(sf::VideoMode({width, height}), "Simulation"), min_r(min_r)
{
    window.setVerticalSyncEnabled(true);

    sf::View view(sf::FloatRect({0.f, 0.f},
                                {static_cast<float>(width),
                                 static_cast<float>(height)}));
    view.setCenter({static_cast<float>(width)  / 2.f,
                    static_cast<float>(height) / 2.f});
    view.setSize  ({static_cast<float>(width), -static_cast<float>(height)});
    window.setView(view);
}

bool SFMLBackend::is_open() const
{
    return window.isOpen();
}

std::vector<SimEvent> SFMLBackend::poll_events()
{
    std::vector<SimEvent> events;
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            events.push_back(SimEvent::Quit);
        } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Space)
                events.push_back(SimEvent::TogglePause);
            else if (key->code == sf::Keyboard::Key::N ||
                     key->code == sf::Keyboard::Key::Tab)
                events.push_back(SimEvent::NextScenario);
        }
    }
    return events;
}

void SFMLBackend::begin_frame()
{
    window.clear();
}

void SFMLBackend::draw_snapshot(const ParticleSnapshot& s)
{
    const auto radius = static_cast<float>(s.radius) + min_r;
    sf::CircleShape circle(radius);
    circle.setOrigin(sf::Vector2f{radius, radius});
    circle.setPosition(sf::Vector2f{static_cast<float>(s.position.x),
                                    static_cast<float>(s.position.y)});
    circle.setFillColor(sf::Color(s.color.r, s.color.g, s.color.b));
    window.draw(circle);
}

void SFMLBackend::draw_particles(const std::vector<ParticleSnapshot>& particles)
{
    for (const auto& s : particles)
        draw_snapshot(s);
}

void SFMLBackend::end_frame()
{
    window.display();
}
