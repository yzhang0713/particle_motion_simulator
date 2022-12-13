#include "Particle.h"

std::ostream& operator<<(std::ostream& os, const Particle& p) {
    os << "Particle " << p.particle_id << " position: " << p.pos << ", velocity: " << p.vel
       << ", radius: " << p.radius;
    return os;
}

void Particle::update_status(const double dt) {
    this->pos += this->vel.scale(dt);
}

double Particle::get_distance(const Particle & other) {
    return (this->pos - other.get_pos()).size();
}

int Particle::check_collision(const Particle & other) {
    int in_collision = 0;
    double distance = this->get_distance(other);
    if (distance < (this->radius + other.get_radius())) {
        in_collision = 1;
    }
    return in_collision;
}