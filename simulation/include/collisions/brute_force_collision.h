#pragma once
#include "collision_algo.h"

class BruteForceCollision : public CollisionAlgo {
    float min_r;
public:
    explicit BruteForceCollision(float min_r) : min_r(min_r) {}
    void resolve(ParticleSystem2D& sys) override;
};
