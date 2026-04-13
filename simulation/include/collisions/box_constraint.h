#pragma once
#include "collision_algo.h"

class BoxConstraint : public CollisionAlgo {
    double right;
    double bottom;
    float  min_r;
public:
    BoxConstraint(double right, double bottom, float min_r) : right(right), bottom(bottom), min_r(min_r) {}
    void resolve(ParticleSystem2D& sys) override;
};
