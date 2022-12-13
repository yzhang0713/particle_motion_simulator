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

    Boundary(Boundary::BoundaryType boundary_type, double boundary_coordinate, int do_reflect) : boundary_type(boundary_type), boundary_coordinate(boundary_coordinate), do_reflect(do_reflect){

    }
    Boundary::BoundaryType get_boundary_type();
    double get_boundary_coordinate();
    int get_do_reflect();
private:
    Boundary::BoundaryType boundary_type;
    double boundary_coordinate;
    int do_reflect;
};


#endif //PARTICLE_MOTION_SIMULATOR_BOUNDARY_H
