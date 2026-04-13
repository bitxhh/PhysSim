#pragma once
#include "scenario.h"

// Солнечная система: Солнце + 4 планеты на круговых орбитах.
// Нет глобальной гравитации, есть попарное ньютоновское тяготение.
class solar_system_scenario final : public scenario {
public:
    std::string name() const override { return "Solar System"; }
    std::unique_ptr<ParticleSystem2D> create(const Config& cfg) const override;
    double   preferred_dt()     const override { return 0.02; }
    unsigned preferred_width()  const override { return 700; }
    unsigned preferred_height() const override { return 700; }
};
