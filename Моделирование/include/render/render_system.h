#pragma once
#include <memory>
#include "../core/particle.h"
#include <functional>


class render_system {
public:

    using creator_t =
        std::function<std::unique_ptr<render_system>(unsigned /*w*/, unsigned /*h*/)>;

    static std::unique_ptr<render_system>
    create(const std::string& backend, unsigned width, unsigned height);


    const unsigned int heights;

    const unsigned int width;

    virtual void update(const std::vector<std::unique_ptr<particle>>& particles) = 0;

    [[nodiscard]] virtual bool is_open() const = 0;

    virtual ~render_system() = 0;

protected:
    render_system(const unsigned int width, const unsigned int heights)
        : heights(heights), width(width) {}

    virtual void check_for_events() = 0;

    virtual void draw(const particle& p) = 0;

    static bool register_backend(const std::string& backend, creator_t creator);
};

