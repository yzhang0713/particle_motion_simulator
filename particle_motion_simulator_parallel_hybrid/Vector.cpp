#include "Vector.h"
#include <math.h>

double Vector::size() {
    return sqrt(x*x + y*y);
}

double Vector::dot(const Vector & other) const {
    return x*other.get_x() + y*other.get_y();
}

Vector Vector::scale(double factor) const {
    return Vector(factor * this->get_x(), factor * this->get_y());
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

Vector Vector::operator+(const Vector& other) const {
    Vector result(this->x + other.get_x(), this->y + other.get_y());
    return result;
}

Vector& Vector::operator+=(const Vector& other) {
    this->x += other.get_x();
    this->y += other.get_y();
    return *this;
}

Vector Vector::operator-(const Vector& other) const {
    Vector result(this->x - other.get_x(), this->y - other.get_y());
    return result;
}

Vector& Vector::operator-=(const Vector& other) {
    this->x -= other.get_x();
    this->y -= other.get_y();
    return *this;
}

Vector Vector::unit_vector() {
    double vec_length = this->size();
    Vector result(this->x/vec_length, this->y/vec_length);
    return result;
}