#include "AsianOption.hpp"
#include <numeric>

using namespace std;

double AsianOption::payoffPath(const vector<double>& path) const {
    double avg = accumulate(path.begin(), path.end(), 0.0) / path.size();
    return payoff(avg);
}

vector<double> AsianOption::getTimeSteps() const { return _timeSteps; }

AsianOption::AsianOption( const vector<double>& timeSteps)
        : Option(timeSteps.back()),_timeSteps(timeSteps) {}

int AsianOption::getNumTimeSteps() const {
    return _timeSteps.size();
}