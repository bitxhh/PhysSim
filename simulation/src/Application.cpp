#include "../include/Application.h"
#include "../include/render/sfml_backend.h"

void Application::load_scene()
{
    // Stop old runner first (jthread destructs → requests stop + joins)
    runner.reset();

    const scenario& scene = scenes.current();
    auto sys = scene.create(cfg);
    backend  = std::make_unique<SFMLBackend>(scene.preferred_width(),
                                             scene.preferred_height(),
                                             cfg.minimal_radius);
    runner   = std::make_unique<SimulationRunner>(std::move(sys), *integ,
                                                  scene.preferred_dt(), buf);
    state    = AppState::Stopped;
}

Application::Application(ScenarioManager scenes_, std::unique_ptr<integrator> integ_, const Config& cfg_)
    : scenes(std::move(scenes_)), cfg(cfg_), integ(std::move(integ_))
{
    load_scene();
}

void Application::run()
{
    while (backend->is_open()) {
        for (const auto e : backend->poll_events()) {
            switch (e) {
            case SimEvent::Quit:
                return;
            case SimEvent::TogglePause:
                state = (state == AppState::Running) ? AppState::Stopped
                                                     : AppState::Running;
                runner->set_running(state == AppState::Running);
                break;
            case SimEvent::NextScenario:
                scenes.next();
                load_scene();
                break;
            }
        }

        backend->begin_frame();
        backend->draw_particles(buf.front_copy());
        backend->end_frame();
    }
}
