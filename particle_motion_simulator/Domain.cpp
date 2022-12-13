#include "Domain.h"
#include "ParticleGenerator.h"
#include "PhysicsEngine.h"

void Domain::set_boundaries(double x_left, double x_right, double y_top, double y_bot) {
    boundaries.push_back(Boundary(Boundary::LEFT, x_left));
    boundaries.push_back(Boundary(Boundary::RIGHT, x_right));
    boundaries.push_back(Boundary(Boundary::TOP, y_top));
    boundaries.push_back(Boundary(Boundary::BOTTOM, y_bot));
}

void Domain::set_particles(double radius, double v_max, int n) {
    this->particles = ParticleGenerator::generate_random_particles(*this, radius, v_max, n);
}

void Domain::time_marching() {
    // Handle contact with boundary
    double x_min, x_max, y_min, y_max;
    for (auto b : boundaries) {
        switch (b.get_boundary_type()) {
            case Boundary::LEFT:
                x_min = b.get_boundary_coordinate();
                break;
            case Boundary::RIGHT:
                x_max = b.get_boundary_coordinate();
                break;
            case Boundary::TOP:
                y_max = b.get_boundary_coordinate();
                break;
            default:
                y_min = b.get_boundary_coordinate();
                break;
        }
    }
    // Check boundary reflection
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
    for (auto & p : particles) {
//        std::cout << p.get_particle_id() << ": " << p.get_pos() << " -> ";
        p.update_status(delta_t);
//        std::cout << p.get_pos() << std::endl;
    }
//    std::cout << "Update particle done" << std::endl;
    this->current_time += this->delta_t;
}

void Domain::record_status(std::ofstream & record_file) {
    record_file << "current time: " << current_time << std::endl;
    for (auto p : particles) {
        record_file << "particle id: " << p.get_particle_id() << "; pos: " << p.get_pos()
                    << "; vel: " << p.get_vel() << std::endl;
    }
}