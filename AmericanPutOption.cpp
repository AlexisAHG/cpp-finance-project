#include "AmericanPutOption.hpp"

using namespace std;

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry), _strike(strike) {}

double AmericanPutOption::payoff(double stockPrice) const {
    return max(0.0, _strike - stockPrice); 
}