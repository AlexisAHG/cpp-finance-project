#include "AmericanOption.hpp"

using namespace std;

AmericanOption::AmericanOption(double expiry) : Option(expiry) {}

bool AmericanOption::isAmericanOption() const {
    return true; 
}