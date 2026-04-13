#pragma once
#include "render_backend.h"
#include <SFML/Graphics.hpp>

class SFMLBackend final : public RenderBackend {
    sf::RenderWindow window;
    float min_r;

    void draw_snapshot(const ParticleSnapshot& s);

public:
    SFMLBackend(unsigned width, unsigned height, float min_r);

    bool is_open() const override;
    std::vector<SimEvent> poll_events() override;
    void begin_frame() override;
    void draw_particles(const std::vector<ParticleSnapshot>& particles) override;
    void end_frame() override;

    ~SFMLBackend() override = default;
};
