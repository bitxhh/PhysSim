#include "../include/config.h"
#include <nlohmann/json.hpp>
#include <fstream>

Config load_config(const std::string& path)
{
    Config cfg;
    std::ifstream f(path);
    if (!f.is_open())
        return cfg;   // файл не найден — используем defaults

    const auto json = nlohmann::json::parse(f);
    if (json.contains("minimal_radius"))
        cfg.minimal_radius = json["minimal_radius"].get<float>();
    if (json.contains("fps"))
        cfg.fps = json["fps"].get<unsigned>();
    return cfg;
}
