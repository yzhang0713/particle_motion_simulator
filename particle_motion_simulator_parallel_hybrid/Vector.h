#ifndef PARTICLE_MOTION_SIMULATOR_VECTOR_H
#define PARTICLE_MOTION_SIMULATOR_VECTOR_H

#include <iostream>

class Vector {
private:
    double x;
    double y;
public:
    Vector() : x(0.0), y(0.0) {

    }
    Vector(double x, double y) : x(x), y(y) {

    }
    void set_x(double x) {
        this->x = x;
    }
    void set_y(double y) {
        this->y = y;
    }
    double get_x() const {
        return x;
    }
    double get_y() const {
        return y;
    }
    double size();
    double dot(const Vector & other) const;
    Vector scale(double factor) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
    Vector operator+(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);
    Vector unit_vector();
};


#endif //PARTICLE_MOTION_SIMULATOR_VECTOR_H
