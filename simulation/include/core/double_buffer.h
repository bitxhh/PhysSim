#pragma once
#include <mutex>

// Sim thread writes to back(), then calls swap().
// Render thread calls front_copy() to get a snapshot under lock.
template<typename T>
class DoubleBuffer {
    T          bufs[2];
    int        read_idx = 0;
    std::mutex mtx;
public:
    T& back() { return bufs[read_idx ^ 1]; }

    void swap() {
        std::lock_guard lock(mtx);
        read_idx ^= 1;
    }

    T front_copy() {
        std::lock_guard lock(mtx);
        return bufs[read_idx];
    }
};
