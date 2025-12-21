#include "EuropeanDigitalOption.hpp"
#include <algorithm>

using namespace std;

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike)
    : Option(expiry), _strike(strike) {}

double EuropeanDigitalOption::payoff(double uPrice) const {
    return 0.0;// Implémentation spécifique pour l'option digitale
}

EuropeanDigitalOption::~EuropeanDigitalOption() = default;