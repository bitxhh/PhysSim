#pragma once
#include <memory>
#include <vector>
#include "config.h"
#include "integrators/integrator.h"
#include "render/render_backend.h"
#include "scenarios/scenario_manager.h"
#include "core/particle_snapshot.h"
#include "core/double_buffer.h"
#include "simulation_runner.h"

enum class AppState { Stopped, Running };

class Application {
    ScenarioManager                             scenes;
    Config                                      cfg;
    std::unique_ptr<integrator>                 integ;
    std::unique_ptr<RenderBackend>              backend;
    std::unique_ptr<SimulationRunner>           runner;
    DoubleBuffer<std::vector<ParticleSnapshot>> buf;
    AppState                                    state = AppState::Stopped;

    void load_scene();

public:
    Application(ScenarioManager scenes, std::unique_ptr<integrator> integ, const Config& cfg);

    void run();
};
