#pragma once

class ParticleSystem2D;

class CollisionAlgo {
public:
    virtual void resolve(ParticleSystem2D& sys) = 0;
    virtual ~CollisionAlgo() = default;
};
