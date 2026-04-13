#pragma once
#include "scenario.h"

// Бильярд: 15 шаров в треугольнике + кий-шар.
// Нет гравитации, есть столкновения, лёгкое затухание (стол).
class billiards_scenario final : public scenario {
public:
    std::string name() const override { return "Billiards"; }
    std::unique_ptr<ParticleSystem2D> create(const Config& cfg) const override;
    double   preferred_dt()     const override { return 0.008; }
    unsigned preferred_width()  const override { return 900; }
    unsigned preferred_height() const override { return 500; }
};
