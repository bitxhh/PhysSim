#include "../../include/render/render_system.h"
#include <unordered_map>

namespace {
    /* Глобальная таблица креаторов */
    using map_t = std::unordered_map<std::string, render_system::creator_t>;
    map_t& registry()
    {
        static map_t m;
        return m;
    }
}

render_system::~render_system() = default;

auto render_system::create(const std::string &backend,
                           const unsigned width,
                           const unsigned height) -> std::unique_ptr<render_system> {
    if (const auto it = registry().find(backend); it != registry().end())
        return (it->second)(width, height);
    std::throw_with_nested(std::runtime_error("Unknown backend: " + backend));
    return nullptr;
}

bool render_system::register_backend(const std::string& backend, creator_t creator)
{
    return registry().emplace(backend, std::move(creator)).second;
}
