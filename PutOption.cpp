#include "PutOption.hpp"
#include <algorithm>

using namespace std;

PutOption::PutOption(double expiry, double strike):EuropeanVanillaOption(expiry,strike){}

double PutOption::payoff(double uPrice) const{
    return max(_strike - uPrice,0.0);
}

EuropeanVanillaOption::optionType PutOption::GetOptionType() const{
    return optionType::Put;
}

PutOption::~PutOption(){}