#pragma once
#include "scenario.h"
#include <vector>
#include <cassert>

class ScenarioManager {
    std::vector<const scenario*> list;
    size_t idx = 0;

public:
    void add(const scenario& s) { list.push_back(&s); }

    const scenario& current() const {
        assert(!list.empty());
        return *list[idx];
    }

    void next() {
        assert(!list.empty());
        idx = (idx + 1) % list.size();
    }

    size_t count() const { return list.size(); }
};
