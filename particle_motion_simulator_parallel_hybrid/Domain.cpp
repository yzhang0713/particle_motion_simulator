#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#include "Domain.h"
#include "ParticleGenerator.h"
#include "PhysicsEngine.h"
#include <omp.h>
#include <float.h>

void Domain::set_boundaries(double x_left, int left_reflect, double x_right, int right_reflect, double y_top, int top_reflect, double y_bot, int bot_reflect) {
    boundaries.push_back(Boundary(Boundary::LEFT, x_left, left_reflect));
    boundaries.push_back(Boundary(Boundary::RIGHT, x_right, right_reflect));
    boundaries.push_back(Boundary(Boundary::TOP, y_top, top_reflect));
    boundaries.push_back(Boundary(Boundary::BOTTOM, y_bot, bot_reflect));
}

void Domain::set_particles(double radius, double v_max, int n, int id_start) {
    this->particles = ParticleGenerator::generate_random_particles(*this, radius, v_max, n, id_start);
}

void Domain::time_marching() {
    // Handle contact with boundary
    double x_min = - DBL_MAX;
    double x_max = DBL_MAX;
    double y_min = - DBL_MAX;
    double y_max = DBL_MAX;
#pragma omp parallel for
    for (auto b : boundaries) {
        switch (b.get_boundary_type()) {
            case Boundary::LEFT:
                if (b.get_do_reflect()) {
                    x_min = b.get_boundary_coordinate();
                }
                break;
            case Boundary::RIGHT:
                if (b.get_do_reflect()) {
                    x_max = b.get_boundary_coordinate();
                }
                break;
            case Boundary::TOP:
                if (b.get_do_reflect()) {
                    y_max = b.get_boundary_coordinate();
                }
                break;
            default:
                if (b.get_do_reflect()) {
                    y_min = b.get_boundary_coordinate();
                }
                break;
        }
    }
    // Check boundary reflection
#pragma omp parallel for
    for (auto & p : particles) {
        if (p.get_pos().get_x() < x_min + p.get_radius()) {
            PhysicsEngine::handle_reflection(p, Boundary::LEFT);
        }
        if (p.get_pos().get_x() > x_max - p.get_radius()) {
            PhysicsEngine::handle_reflection(p, Boundary::RIGHT);
        }
        if (p.get_pos().get_y() < y_min + p.get_radius()) {
            PhysicsEngine::handle_reflection(p, Boundary::BOTTOM);
        }
        if (p.get_pos().get_y() > y_max - p.get_radius()) {
            PhysicsEngine::handle_reflection(p, Boundary::TOP);
        }
    }
//    std::cout << "Check boundary done" << std::endl;
//    std::cout << "Particle number: " << particles.size() << std::endl;
    // Check particle collision
#pragma omp parallel for
    for (int i = 0; i < particles.size() - 1; i++) {
        Particle p1 = particles.at(i);
        for (int j = i+1; j < particles.size(); j++) {
            Particle p2 = particles.at(j);
//            std::cout << "\tChecking between particle " << i << " and " << j << std::endl;
            if (p1.check_collision(p2)) {
                PhysicsEngine::handle_collision(p1, p2);
            }
        }
    }
//    std::cout << "Check particle collision done" << std::endl;
    // Update particle position
#pragma omp parallel for
    for (auto & p : particles) {
//        std::cout << p.get_particle_id() << ": " << p.get_pos() << " -> ";
        p.update_status(delta_t);
//        std::cout << p.get_pos() << std::endl;
    }
//    std::cout << "Update particle done" << std::endl;
    this->current_time += this->delta_t;
}

void Domain::update_particle_buffer() {
    int i = 0;
    int element_to_move = 0;
    while (i < particles.size() - element_to_move) {
        if (do_oob_check(particles.at(i))) {
            std::iter_swap(particles.begin() + i, particles.begin() + (particles.size() - 1 - element_to_move));
            element_to_move++;
        } else {
            i++;
        }
    }
    if (element_to_move > 0) {
        particle_buffer.insert(particle_buffer.end(), std::make_move_iterator(particles.begin() + (i-1)), std::make_move_iterator(particles.end()));
        particles.erase(particles.begin() + (i-1), particles.end());
    }
}

int Domain::extract_particle_buffer(MPIPoint *out_buffer) {
    int out_particles = particle_buffer.size();
    MPIUtils::convertParticleToMPIPoint(out_buffer, particle_buffer);
    return out_particles;
}

void Domain::update_particles(std::vector<Particle> &added_particles) {
    if (added_particles.size() > 0) {
        particles.insert(particles.end(), std::make_move_iterator(added_particles.begin()), std::make_move_iterator(added_particles.end()));
        added_particles.clear();
    }
}

void Domain::clear_particle_buffer() {
    particle_buffer.clear();
}

void Domain::record_status(std::ofstream & record_file) {
    record_file << "current time: " << current_time << std::endl;
    for (auto p : particles) {
        record_file << "particle id: " << p.get_particle_id() << "; pos: " << p.get_pos()
                    << "; vel: " << p.get_vel() << std::endl;
    }
}
#pragma clang diagnostic pop