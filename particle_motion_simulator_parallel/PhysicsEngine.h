#ifndef PARTICLE_MOTION_SIMULATOR_PHYSICSENGINE_H
#define PARTICLE_MOTION_SIMULATOR_PHYSICSENGINE_H


#include "Particle.h"
#include "Boundary.h"

class PhysicsEngine {
public:
    void static handle_collision(Particle & p1, Particle & p2);
    void static handle_reflection(Particle & p1, Boundary::BoundaryType boundary);
};


#endif //PARTICLE_MOTION_SIMULATOR_PHYSICSENGINE_H
