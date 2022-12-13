//
// Created by yuzhang on 12/12/2022.
//

#include "MPIUtils.h"

void MPIUtils::convertParticleToMPIPoint(MPIPoint *mpi_points, std::vector<Particle> & particles) {
    int n_particle = particles.size();
    for (int i = 0; i < n_particle; i++) {
        mpi_points[i].id = particles.at(i).get_particle_id();
        mpi_points[i].x_pos = particles.at(i).get_pos().get_x();
        mpi_points[i].y_pos = particles.at(i).get_pos().get_y();
        mpi_points[i].x_vel = particles.at(i).get_vel().get_x();
        mpi_points[i].y_vel = particles.at(i).get_vel().get_y();
        mpi_points[i].radius = particles.at(i).get_radius();
    }
}

void MPIUtils::convertMPIPointToParticle(MPIPoint *mpi_points, std::vector<Particle> & particles, int n_particle) {
    for (int i = 0; i < n_particle; i++) {
        particles.push_back(Particle(mpi_points[i].id, Vector(mpi_points[i].x_pos, mpi_points[i].y_pos), Vector(mpi_points[i].x_vel, mpi_points[i].y_vel), mpi_points[i].radius));
    }
}