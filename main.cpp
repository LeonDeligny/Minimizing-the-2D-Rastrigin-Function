/*
Minimizing the 2D Rastrigin Function.

The Rastrigin function is commonly used for testing optimization algorithms due to its many local minima, 
which makes finding the global minimum challenging. The function in 2D is defined as follows:

            f(x, y) = 20 + x^2 + y^2 - 10(\cos(2 \pi x) + \cos(2 \pi y)).

*/

#include <iostream>
#include <cmath>

const double PI = 3.14159265358979323846;
const double TWO_PI = 2*PI;

// Struct to hold graph information
struct Graph {
    double x;
    double y;
    double energy;
};

// Rastrigin function (Equivalent of Energy function)
double rastrigin(double x, double y) {
    return 20 + x*x + y*y - 10 * (cos(TWO_PI * x) + cos(TWO_PI * y));
}

// Cost Difference (Actual to New state)
double cost_difference(double new_x, double new_y, double x, double y) {
    return (rastrigin(new_x, new_y) - rastrigin(x, y));
}

// State Change (adding a small random variation to the state)
double state_change(double x) {    
    return x + ((rand() / (double)RAND_MAX) - 0.5); // Variation in the range [-0.5, 0.5]
}

// Simulated Annealing Function
Graph simulated_annealing(int max_iterations = 10000000, double T = 100.0, double alpha = 0.9999999, double min_temp = 1e-5, int log_interval = 1000) {
    // Set seed randomly
    srand(time(0));

    // Initial State
    double x = 10 * ((rand() / (double)RAND_MAX) - 0.5); // x in interval [-5, 5]
    double y = 10 * ((rand() / (double)RAND_MAX) - 0.5); // y in interval [-5, 5]

    // Energy of initial state
    double energy = rastrigin(x, y);
    
    Graph best_graph = {x, y, energy}; // Initialize best graph with initial state
    
    for (int i = 0; i < max_iterations && T > min_temp; ++i) {
        // Generate new state
        double new_x = state_change(x);
        double new_y = state_change(y);
        double new_energy = rastrigin(new_x, new_y);
        
        double cost_diff = new_energy - energy;

        // Accept new state with probability based on cost difference and temperature
        if (cost_diff < 0 || exp(-cost_diff / T) > rand()/double(RAND_MAX)) {
            x = new_x;
            y = new_y;
            energy = new_energy;
            
            // Update best state if new state is better
            if (new_energy < best_graph.energy) {
                best_graph.x = new_x;
                best_graph.y = new_y;
                best_graph.energy = new_energy;
            }
        }
        
        T *= alpha; // Cooling Schedule

        if (i % log_interval == 0) {
            std::cout << "Iteration: " << i << ", x: " << x << ", y: " << y << ", Energy: " << energy << ", Temperature: " << T << std::endl;
        }
    }
    
    return best_graph;
}

int main() {
    Graph best_state = simulated_annealing();
    std::cout << "Best State Found: x = " << best_state.x << ", y = " << best_state.y << ", Energy = " << best_state.energy << std::endl;
    return 0;
}