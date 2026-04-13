#pragma once
#include <string>

struct Config {
    float    minimal_radius = 3.f;
    unsigned fps            = 60;
};

Config load_config(const std::string& path);
