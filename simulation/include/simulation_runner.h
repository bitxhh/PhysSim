#pragma once
#include <atomic>
#include <thread>
#include <memory>
#include <vector>
#include "core/particle_system.h"
#include "core/particle_snapshot.h"
#include "core/double_buffer.h"
#include "integrators/integrator.h"

class SimulationRunner {
    std::unique_ptr<ParticleSystem2D>             sys;
    integrator&                                  integ;
    double                                       dt;
    DoubleBuffer<std::vector<ParticleSnapshot>>& buf;
    std::atomic<bool>                            running{false};
    std::jthread                                 thread;

    void loop(std::stop_token stop);

public:
    SimulationRunner(std::unique_ptr<ParticleSystem2D> sys,
                     integrator& integ,
                     double dt,
                     DoubleBuffer<std::vector<ParticleSnapshot>>& buf);

    void set_running(bool r) { running.store(r, std::memory_order_relaxed); }
};
