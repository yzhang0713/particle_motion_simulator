#include "ParticleGenerator.h"

std::vector<Particle> ParticleGenerator::generate_random_particles(Domain & domain, double radius, double v_max, int n, int id_start) {
    std::vector<Boundary> boundaries = domain.get_boundaries();
    std::vector<Particle> particles;
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
    srand((unsigned)time(NULL));
    int particle_count = 0;
    while (particle_count < n) {
        Particle p(id_start);
        id_start++;
        p.set_radius(radius);
        // Generate x position
        double x = ((double)rand()/(double)RAND_MAX) * (x_max - x_min) + x_min;
        // Generate y position
        double y = ((double)rand()/(double)RAND_MAX) * (y_max - y_min) + y_min;
        p.set_pos(Vector(x, y));
        // Generate velocity direction x
        double x_dir = (double)rand()/(double)RAND_MAX * 2.0 - 1.0;
        double y_dir = (double)rand()/(double)RAND_MAX * 2.0 - 1.0;
        double v = (((double)rand()/(double)RAND_MAX)) * v_max;
        p.set_vel(Vector(x_dir, y_dir).unit_vector().scale(v));
        particles.push_back(p);
        particle_count++;
    }
//    std::cout << "Particles generated: " << particles.size() << std::endl;
    return particles;
}