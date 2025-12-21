#include "EuropeanDigitalPutOption.hpp"

using namespace std;

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalPutOption::payoff(double z) const {
    return (z <= _strike) ? 1.0 : 0.0; // "?" permet de faire un if else en une ligne
}
    
EuropeanDigitalOption::optionType EuropeanDigitalPutOption::GetOptionType() const {
    return Put;
}