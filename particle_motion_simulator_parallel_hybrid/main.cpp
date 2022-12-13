#include <iostream>
#include "Domain.h"
#include <fstream>
#include <ctime>
#include "MPIUtils.h"
#include <sstream>
#include <string>
#include <mpi.h>

int main(int argc, char **argv) {

    int rank, num;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &num);

    if (num != 2) {
        std::cout << "This application is meant to be run with 2 processes." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Declare custom type for particle to be transmitted through MPI
    int lengths[6] = {1, 1, 1, 1, 1, 1};
    MPI_Datatype types[6] = {MPI_INT, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE};
    MPI_Aint displacements[6];
    MPIPoint dummy_mpi_point;
    MPI_Aint base_address;
    MPI_Get_address(&dummy_mpi_point, &base_address);
    MPI_Get_address(&dummy_mpi_point.id, &displacements[0]);
    MPI_Get_address(&dummy_mpi_point.x_pos, &displacements[1]);
    MPI_Get_address(&dummy_mpi_point.y_pos, &displacements[2]);
    MPI_Get_address(&dummy_mpi_point.x_vel, &displacements[3]);
    MPI_Get_address(&dummy_mpi_point.y_vel, &displacements[4]);
    MPI_Get_address(&dummy_mpi_point.radius, &displacements[5]);
    displacements[0] = MPI_Aint_diff(displacements[0], base_address);
    displacements[1] = MPI_Aint_diff(displacements[1], base_address);
    displacements[2] = MPI_Aint_diff(displacements[2], base_address);
    displacements[3] = MPI_Aint_diff(displacements[3], base_address);
    displacements[4] = MPI_Aint_diff(displacements[4], base_address);
    displacements[5] = MPI_Aint_diff(displacements[5], base_address);
    MPI_Datatype mpi_particle;
    MPI_Type_create_struct(6, lengths, displacements, types, &mpi_particle);
    MPI_Type_commit(&mpi_particle);

    // Configure domain with size 2000 x 2000
    Domain domain{};
    domain.set_current_time(0.0);
    domain.set_delta_t(0.001);
    if (rank == 0) {
        domain.set_boundaries(-100.0, 1,0.0, 0, 100.0, 1, -100.0, 1);
        domain.set_particles(1.0, 1.0, 500, 0);
        domain.set_oob_check([](Particle p) {
            return p.get_pos().get_x() > (0.0 - p.get_radius());
        });
    } else {
        domain.set_boundaries(0.0, 0,100.0, 1, 100.0, 1, -100.0, 1);
        domain.set_particles(1.0, 1.0, 500, 500);
        domain.set_oob_check([](Particle p) {
            return p.get_pos().get_x() < (0.0 + p.get_radius());
        });
    }

//    std::cout << "Set domain done" << std::endl;
    // Open record file
    std::ostringstream oss;
    oss << "domain_record_" << rank << ".txt";
    std::ofstream record_file(oss.str());
    // Start simulation
    double t_end = 10.0;
    int step_counter = 0;
    int record_steps = 100;
    time_t start_time;
    start_time = time(NULL);
    std::cout << "Start simulation from node " << rank << ": " << start_time << std::endl;
    // Data transfer buffer, assuming at most 50 particles need to be transmitted
    MPIPoint in_buffer[50];
    MPIPoint out_buffer[50];
    MPI_Status st;
    while (domain.get_current_time() < t_end) {
        domain.time_marching();
        domain.update_particle_buffer();
        int out_particles = domain.extract_particle_buffer(out_buffer);
        // Start communication
        if (rank == 0) {
            // For rank 0, send first, then receive
            MPI_Send(out_buffer, out_particles, mpi_particle, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(in_buffer, 50, mpi_particle, 1, 1, MPI_COMM_WORLD, &st);
        } else {
            // For rank 1, receive first, then send
            MPI_Recv(in_buffer, 50, mpi_particle, 0, 0, MPI_COMM_WORLD, &st);
            MPI_Send(out_buffer, out_particles, mpi_particle, 0, 1, MPI_COMM_WORLD);
        }
        // Get number of input particles
        int in_particles;
        MPI_Get_count(&st, mpi_particle, &in_particles);
        // Clear particle buffer
        domain.clear_particle_buffer();
        // Convert received particles to particle vector
        std::vector<Particle> incoming_particles;
        MPIUtils::convertMPIPointToParticle(in_buffer, incoming_particles, in_particles);
        domain.update_particles(incoming_particles);
        step_counter++;
        if (step_counter == record_steps) {
            std::cout << "Writing record for simulation time from node " << rank << ": " << domain.get_current_time() << std::endl;
            domain.record_status(record_file);
            step_counter = 0;
        }
    }
    std::cout << "Simulation time: " << time(NULL) - start_time << " seconds." << std::endl;
    // Close record file
    record_file.close();
    MPI_Finalize();
    return 0;
}
