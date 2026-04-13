#include "../include/simulation_runner.h"
#include <chrono>

static std::vector<ParticleSnapshot> make_snapshot(const ParticleSystem2D& sys)
{
    std::vector<ParticleSnapshot> snap;
    snap.reserve(sys.particles.size());
    for (const auto& p : sys.particles)
        snap.push_back({p->position, p->radius, p->material_type.color});
    return snap;
}

SimulationRunner::SimulationRunner(std::unique_ptr<ParticleSystem2D> sys_,
                                   integrator& integ_,
                                   double dt_,
                                   DoubleBuffer<std::vector<ParticleSnapshot>>& buf_)
    : sys(std::move(sys_)), integ(integ_), dt(dt_), buf(buf_)
{
    // Publish initial frame so the render thread never reads an empty buffer
    buf.back() = make_snapshot(*sys);
    buf.swap();

    thread = std::jthread([this](std::stop_token st) { loop(st); });
}

void SimulationRunner::loop(std::stop_token stop)
{
    using namespace std::chrono_literals;
    while (!stop.stop_requested()) {
        if (running.load(std::memory_order_relaxed)) {
            sys->step(dt, integ);
            buf.back() = make_snapshot(*sys);
            buf.swap();
        } else {
            std::this_thread::sleep_for(1ms);
        }
    }
}
