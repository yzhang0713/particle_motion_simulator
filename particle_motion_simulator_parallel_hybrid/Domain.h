#ifndef PARTICLE_MOTION_SIMULATOR_DOMAIN_H
#define PARTICLE_MOTION_SIMULATOR_DOMAIN_H

#include <vector>
#include "Boundary.h"
#include "Particle.h"
#include <fstream>
#include <iostream>
#include <functional>
#include "MPIUtils.h"

class Domain {
private:
    std::vector<Boundary> boundaries;
    std::vector<Particle> particles;
    std::vector<Particle> particle_buffer;
    double current_time;
    double delta_t;
    std::function<int(Particle)> oob_check;
public:
    void set_oob_check(std::function<int(Particle)> f) {
        oob_check = std::move(f);
    }
    int do_oob_check(Particle p) {
        return oob_check(p);
    }
    void update_particle_buffer();
    void update_particles(std::vector<Particle> & added_particles);
    void clear_particle_buffer();
    int extract_particle_buffer(MPIPoint* out_buffer);
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
    void set_boundaries(double x_left, int left_reflect, double x_right, int right_reflect, double y_top, int top_reflect, double y_bot, int bot_reflect);
    void set_particles(double radius, double v_max, int n, int id_start);
    void time_marching();
    void record_status(std::ofstream & record_file);
};


#endif //PARTICLE_MOTION_SIMULATOR_DOMAIN_H
