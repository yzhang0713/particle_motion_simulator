#ifndef PARTICLE_MOTION_SIMULATOR_DOMAIN_H
#define PARTICLE_MOTION_SIMULATOR_DOMAIN_H

#include <vector>
#include "Boundary.h"
#include "Particle.h"
#include <fstream>
#include <iostream>

class Domain {
private:
    std::vector<Boundary> boundaries;
    std::vector<Particle> particles;
    double current_time;
    double delta_t;
public:
    void set_current_time(double t) {
        current_time = t;
    }
    double get_current_time() const {
        return current_time;
    }
    void set_delta_t(double dt) {
        delta_t = dt;
    }
    double get_delta_t() const {
        return delta_t;
    }
    std::vector<Boundary> & get_boundaries() {
        return boundaries;
    }
    std::vector<Particle> & get_particles() {
        return particles;
    }
    void set_boundaries(double x_left, double x_right, double y_top, double y_bot);
    void set_particles(double radius, double v_max, int n);
    void time_marching();
    void record_status(std::ofstream & record_file);
};


#endif //PARTICLE_MOTION_SIMULATOR_DOMAIN_H
