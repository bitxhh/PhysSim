#pragma once
#include "sim_event.h"
#include "../core/particle_snapshot.h"
#include <vector>

class RenderBackend {
public:
    virtual bool is_open() const = 0;
    virtual std::vector<SimEvent> poll_events() = 0;
    virtual void begin_frame() = 0;
    virtual void draw_particles(const std::vector<ParticleSnapshot>& particles) = 0;
    virtual void end_frame() = 0;
    virtual ~RenderBackend() = default;
};
