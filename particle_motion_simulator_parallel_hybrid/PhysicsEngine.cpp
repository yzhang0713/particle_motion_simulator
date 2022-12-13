#include "PhysicsEngine.h"

void PhysicsEngine::handle_collision(Particle &p1, Particle &p2) {
    Vector dir = (p2.get_pos() - p1.get_pos()).unit_vector();
    Vector p1_vel_dir = p1.get_vel().scale(p1.get_vel().dot(dir));
    Vector p1_vel_per = p1.get_vel() - p1_vel_dir;
    Vector p2_vel_dir = p2.get_vel().scale(p2.get_vel().dot(dir.scale(-1.0)));
    Vector p2_vel_per = p2.get_vel() - p2_vel_dir;
    p1.set_vel(p1_vel_dir.scale(-1.0) + p1_vel_per);
    p2.set_vel(p2_vel_dir.scale(-1.0) + p2_vel_per);
}

void PhysicsEngine::handle_reflection(Particle &p, Boundary::BoundaryType boundary) {
    Vector dir{};
    switch (boundary) {
        case Boundary::LEFT:
            dir.set_x(-1.0);
            break;
        case Boundary::RIGHT:
            dir.set_x(1.0);
            break;
        case Boundary::TOP:
            dir.set_y(1.0);
            break;
        default:
            dir.set_y(-1.0);
            break;
    }
    Vector p_vel_dir = p.get_vel().scale(p.get_vel().dot(dir));
    Vector p_vel_per = p.get_vel() - p_vel_dir;
    p.set_vel(p_vel_dir.scale(-1.0) + p_vel_per);
}