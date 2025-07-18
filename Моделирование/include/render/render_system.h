#pragma once
#include <memory>
#include <string>
#include "../core/particle.h"


class render_system {
public:
    static std::unique_ptr<render_system>
    init(const std::string &window_type,
         unsigned int width,
         unsigned int heights);

    unsigned int heights;

    unsigned int width;

    virtual void update(const std::vector<std::unique_ptr<particle>>& particles) = 0;

    [[nodiscard]] virtual bool is_open() const = 0;

    virtual ~render_system() = default;

protected:
    render_system(const unsigned int width, const unsigned int heights)
        : heights(heights), width(width) {}

    virtual void check_for_events() = 0;

    virtual void draw(const particle& p) = 0;
};

