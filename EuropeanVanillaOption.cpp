#include "EuropeanVanillaOption.hpp"

using namespace std;

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike):Option(expiry),_strike(strike){
    if(expiry<0||strike<0)
    {
        throw invalid_argument("Arguments are negative");
    }
}

double EuropeanVanillaOption::getStrike() const{
    return _strike;
}

EuropeanVanillaOption::~EuropeanVanillaOption(){};