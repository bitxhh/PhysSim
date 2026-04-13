#pragma once
#include "render_backend.h"

// No-op рендер для тестов. is_open() возвращает true первые max_frames кадров.
class HeadlessBackend final : public RenderBackend {
    int remaining;
public:
    explicit HeadlessBackend(int max_frames) : remaining(max_frames) {}

    bool is_open() const override { return remaining > 0; }
    std::vector<SimEvent> poll_events() override { return {}; }
    void begin_frame()  override { --remaining; }
    void draw_particles(const std::vector<ParticleSnapshot>&) override {}
    void end_frame()    override {}
};
