#include "EuropeanDigitalCallOption.hpp"

using namespace std;

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalCallOption::payoff(double z) const {
    return (z >= _strike) ? 1.0 : 0.0; // "?" permet de faire un if else en une ligne 
}

EuropeanDigitalCallOption::optionType EuropeanDigitalCallOption::GetOptionType() const {
    return Call;
}