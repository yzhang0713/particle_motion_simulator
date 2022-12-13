//
// Created by yuzhang on 12/12/2022.
//

#ifndef PARTICLE_MOTION_SIMULATOR_PARALLEL_MPIUTILS_H
#define PARTICLE_MOTION_SIMULATOR_PARALLEL_MPIUTILS_H

#include <vector>
#include "Particle.h"

typedef struct MPIPoint
{
    int id;
    double x_pos;
    double y_pos;
    double x_vel;
    double y_vel;
    double radius;
} MPIPoint;

class MPIUtils {
public:
    void static convertParticleToMPIPoint(MPIPoint* mpi_points, std::vector<Particle> & particles);
    void static convertMPIPointToParticle(MPIPoint* mpi_points, std::vector<Particle> & particles, int n_particle);
};


#endif //PARTICLE_MOTION_SIMULATOR_PARALLEL_MPIUTILS_H
