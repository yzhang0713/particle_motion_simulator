#ifndef PARTICLE_MOTION_SIMULATOR_PARTICLE_H
#define PARTICLE_MOTION_SIMULATOR_PARTICLE_H
#include "Vector.h"

class Particle {
private:
    static int ID;
    const int particle_id;
    Vector pos;
    Vector vel;
    double radius;
public:
    Particle() : particle_id(ID++), pos(Vector{}), vel(Vector{}), radius(0.0) {

    }
    void set_pos(const Vector& pos) {
        this->pos.set_x(pos.get_x());
        this->pos.set_y(pos.get_y());
    }
    void set_vel(const Vector& vel) {
        this->vel.set_x(vel.get_x());
        this->vel.set_y(vel.get_y());
    }
    void set_radius(const double radius) {
        this->radius = radius;
    }
    Vector get_pos() const {
        return Vector(this->pos.get_x(), this->pos.get_y());
    }
    Vector get_vel() const {
        return Vector(this->vel.get_x(), this->vel.get_y());
    }
    double get_radius() const {
        return this->radius;
    }
    int get_particle_id() const {
        return this->particle_id;
    }
    friend std::ostream& operator<<(std::ostream& os, const Particle& p);
    void update_status(const double dt);
    int check_collision(const Particle & other);
    double get_distance(const Particle & other);

};


#endif //PARTICLE_MOTION_SIMULATOR_PARTICLE_H
