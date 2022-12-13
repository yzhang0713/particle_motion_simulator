cmake_minimum_required(VERSION 3.0)
project(particle_motion_simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(particle_motion_simulator main.cpp particle.cpp particle.h Vector.cpp Vector.h PhysicsEngine.cpp PhysicsEngine.h ParticleGenerator.cpp ParticleGenerator.h Domain.cpp Domain.h Boundary.cpp Boundary.h)
