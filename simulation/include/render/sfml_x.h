#pragma once
#include <SFML/Graphics.hpp>
#include "render_system.h"

class sfml_window final : public render_system {
    sf::RenderWindow window;

    void check_for_events() override;
    void draw(const particle& p) override;

public:
    explicit sfml_window(unsigned width, unsigned height);

    static std::unique_ptr<render_system>
    create_window(unsigned width, unsigned height);

    [[nodiscard]] bool is_open() const override;

    void update(const std::vector<std::unique_ptr<particle>>& particles) override;

    ~sfml_window() override = default;

private:
    inline static const bool registered =
        register_backend("SFML", create_window);
};