#include "Boundary.h"

Boundary::BoundaryType Boundary::get_boundary_type() {
    return boundary_type;
}

double Boundary::get_boundary_coordinate() {
    return boundary_coordinate;
}

int Boundary::get_do_reflect() {
    return do_reflect;
}