#ifndef PARTICLE_MOTION_SIMULATOR_PARTICLEGENERATOR_H
#define PARTICLE_MOTION_SIMULATOR_PARTICLEGENERATOR_H

#include <vector>
#include "Particle.h"
#include "Domain.h"

class ParticleGenerator {
public:
    std::vector<Particle> static generate_random_particles(Domain & domain, double radius, double v_max, int n, int id_start);
};


#endif //PARTICLE_MOTION_SIMULATOR_PARTICLEGENERATOR_H
