#include <iostream>
#include "Domain.h"
#include <fstream>
#include <ctime>

int main() {
    // Configure domain with size 2000 x 2000
    Domain domain{};
    domain.set_current_time(0.0);
    domain.set_delta_t(0.001);
    domain.set_boundaries(-100.0, 100.0, 100.0, -100.0);
    domain.set_particles(1.0, 1.0, 1000);
//    std::cout << "Set domain done" << std::endl;
    // Open record file
    std::ofstream record_file("domain_record.txt");
    // Start simulation
    double t_end = 10.0;
    int step_counter = 0;
    int record_steps = 100;
    time_t start_time;
    start_time = time(NULL);
    std::cout << "Start simulation: " << start_time << std::endl;
    while (domain.get_current_time() < t_end) {
        domain.time_marching();
        step_counter++;
        if (step_counter == record_steps) {
            std::cout << "Writing record for simulation time: " << domain.get_current_time() << std::endl;
            domain.record_status(record_file);
            step_counter = 0;
        }
    }
    std::cout << "Simulation time: " << time(NULL) - start_time << " seconds." << std::endl;
    // Close record file
    record_file.close();
    return 0;
}
