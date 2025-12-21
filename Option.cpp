#include "Option.hpp"
#include <vector>

using namespace std;

Option::Option(double expiry):_expiry(expiry){}

double Option::getExpiry() const{ 
    return _expiry;
}

double Option::payoffPath(const vector<double>& path) const { // Permet de calculer le payoff d'une option sur un chemin
    return payoff(path.back());
}

Option::~Option()=default;