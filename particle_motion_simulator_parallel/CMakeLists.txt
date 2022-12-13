cmake_minimum_required(VERSION 3.0)
project(particle_motion_simulator_parallel)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(particle_motion_simulator main.cpp particle.cpp particle.h Vector.cpp Vector.h PhysicsEngine.cpp PhysicsEngine.h ParticleGenerator.cpp ParticleGenerator.h Domain.cpp Domain.h Boundary.cpp Boundary.h)
