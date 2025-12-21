#include "AsianPutOption.hpp"
#include <algorithm>

using namespace std;

AsianPutOption::AsianPutOption(const vector<double>& timeSteps, double strike)
        : AsianOption(timeSteps), _strike(strike) {}

double AsianPutOption::payoff(double S) const {
    return max(_strike - S, 0.0);
}