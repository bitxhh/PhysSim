#pragma once
#include <memory>
#include <string>
#include "../core/particle_system.h"
#include "../config.h"

// Базовый класс сценария.
// Создаёт и настраивает ParticleSystem2D — начальные условия,
// физику, размеры окна.
class scenario {
public:
    virtual ~scenario() = default;

    virtual std::string name() const = 0;

    // Создаёт и полностью настраивает систему частиц
    virtual std::unique_ptr<ParticleSystem2D> create(const Config& cfg) const = 0;

    // Предпочтительный шаг времени
    virtual double preferred_dt() const { return 0.016; }

    // Размеры окна
    virtual unsigned preferred_width()  const { return 800; }
    virtual unsigned preferred_height() const { return 600; }
};
