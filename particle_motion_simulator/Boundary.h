#ifndef PARTICLE_MOTION_SIMULATOR_BOUNDARY_H
#define PARTICLE_MOTION_SIMULATOR_BOUNDARY_H


class Boundary {

public:

    enum BoundaryType {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };

    Boundary(Boundary::BoundaryType boundary_type, double boundary_coordinate) : boundary_type(boundary_type), boundary_coordinate(boundary_coordinate){

    }
    Boundary::BoundaryType get_boundary_type();
    double get_boundary_coordinate();
private:
    Boundary::BoundaryType boundary_type;
    double boundary_coordinate;
};


#endif //PARTICLE_MOTION_SIMULATOR_BOUNDARY_H
