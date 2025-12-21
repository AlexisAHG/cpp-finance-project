#include "BlackScholesMCPricer.hpp"
#include "MT.hpp"
#include <cmath>
#include <stdexcept>
#include <numeric>

using namespace std;

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initialPrice, double interestRate, double volatility)
    : _option(option), _initialPrice(initialPrice), _interestRate(interestRate), _volatility(volatility), _numPaths(0), _priceEstimate(0.0) {
    if (option->isAsianOption()) {
        cout<<"Asian options not supported in CRRPricer"<<endl;
    }
}



double BlackScholesMCPricer::operator()() const {
    if (_numPaths == 0) throw runtime_error("No paths");
    return _priceEstimate;
}

vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_numPaths == 0) throw std::runtime_error("No paths");
    vector<double> payoffs;

    double meanPayoff = accumulate(payoffs.begin(), payoffs.end(), 0.0) / payoffs.size();
    double variance = 0.0;
    for (const auto& payoff : payoffs) {
        variance += (payoff - meanPayoff) * (payoff - meanPayoff);
    }
    variance /= payoffs.size();

    double stddev = std::sqrt(variance);
    double marginOfError = 1.96 * (stddev / std::sqrt(payoffs.size())); 

    vector<double> confidenceInterval(2);
    confidenceInterval[0] = _priceEstimate - marginOfError;
    confidenceInterval[1] = _priceEstimate + marginOfError;

    return confidenceInterval; 
}

void BlackScholesMCPricer::generate(int nb_paths) {
    _numPaths += nb_paths;
    vector<double> payoffs(nb_paths);

    double dt = _option->getExpiry();
    int numSteps = 50; 
    double stepDt = dt / numSteps;

    for (int i = 0; i < nb_paths; ++i) {
        if (_option->isAsianOption()) {
            vector<double> path(numSteps);  // Simulation d'un chemin pour une option asiatique
            double price = _initialPrice;

            for (int j = 0; j < numSteps; ++j) {
                double randomNorm = MT::rand_norm();
                price *= exp((_interestRate - 0.5 * _volatility * _volatility) * stepDt + _volatility * randomNorm * sqrt(stepDt));
                path[j] = price; 
            }

            payoffs[i] = _option->payoffPath(path); // Utilisation de payoffPath pour calculer le payoff du chemin
        } else {
            double price = _initialPrice;   // Simulation classique pour une option européenne
            double randomNorm = MT::rand_norm();
            double St = price * exp((_interestRate - 0.5 * _volatility * _volatility) * dt + _volatility * randomNorm * sqrt(dt));
            
            payoffs[i] = _option->payoff(St);
        }
    }

    double sumPayoffs = accumulate(payoffs.begin(), payoffs.end(), 0.0);
    _priceEstimate = exp(-_interestRate * dt) * (sumPayoffs / nb_paths);
}