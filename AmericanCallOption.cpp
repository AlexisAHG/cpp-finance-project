#include "AmericanCallOption.hpp"

using namespace std;

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

double AmericanCallOption::payoff(double stockPrice) const {
    return max(0.0, stockPrice - _strike); 
}