#include "MT.hpp"

using namespace std;

mt19937 MT::generator((random_device())()); // Initialisation du générateur

double MT::rand_unif() { 
    uniform_real_distribution<double> dist(0.0, 1.0); // Distribution uniforme entre 0 et 1
    return dist(generator);
}

double MT::rand_norm() {
    normal_distribution<double> dist(0.0, 1.0); // Distribution normale centrée réduite
    return dist(generator);
}  