#include "CallOption.hpp"
#include <algorithm>

using namespace std;

CallOption::CallOption(double expiry, double strike):EuropeanVanillaOption(expiry,strike){}

double CallOption::payoff(double uPrice) const{
    return max(uPrice - _strike,0.0);
}

EuropeanVanillaOption::optionType CallOption::GetOptionType() const {
    return optionType::Call; 
}

CallOption::~CallOption(){}  