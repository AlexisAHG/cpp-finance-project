#include "AsianCallOption.hpp"
#include <algorithm>

using namespace std;

AsianCallOption::AsianCallOption(const vector<double>& timeSteps, double strike)
        : AsianOption(timeSteps), _strike(strike) {}

double AsianCallOption::payoff(double S) const {
    return max(S - _strike, 0.0);
}