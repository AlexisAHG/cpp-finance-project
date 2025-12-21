#include "BlackScholesPricer.hpp"
#include "MT.hpp"  
#include <cmath>   

using namespace std;

// Fonction de répartition de la distribution normale (CDF)
double N(double x) {
    return 0.5 * erfc(-x / sqrt(2));  
}

// Densité de la distribution normale
double n(double x) {
    return exp(-0.5 * x * x) / sqrt(2 * M_PI);  
}

BlackScholesPricer::BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility)
    : _option(option), _assetPrice(asset_price), _interestRate(interest_rate), _volatility(volatility) {
    if (option->isAsianOption()) {
        cout << "Asian options not supported in CRRPricer" << endl;
    }
} 

BlackScholesPricer::BlackScholesPricer(EuropeanDigitalOption* option, double asset_price, double interest_rate, double volatility)
    : _digitalOption(option), _assetPrice(asset_price), _interestRate(interest_rate), _volatility(volatility) {
    if (option->isAsianOption()) {
        cout << "Asian options not supported in CRRPricer" << endl;
    }
} 

// Fonction d'évaluation de l'option, elle est utilisée via l'opérateur ()
double BlackScholesPricer::operator()() const {
    
   double T, K;
    if (_option) {
        T = _option->getExpiry();
        K = _option->_strike;
    }
    // Si l'option est de type Digital
    else if (_digitalOption) {
       
        T = _digitalOption->getExpiry();
        K = _digitalOption->_strike;
    }
   
    double S = _assetPrice;
    double r = _interestRate;
    double sigma = _volatility;
   
 
    if(T<=0.0){
        throw std::invalid_argument("Expiry must be positive");
    }
 
    double d1 = (log(S/K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
 
    double d2 = d1 - sigma * sqrt(T);
    if (_option) {
        if (_option ->GetOptionType() == EuropeanVanillaOption::Call) {
            return S * N(d1) - K * exp(-r*T) * N(d2);
        }else {
            return K * exp(-r*T) * N(-d2) - S * N(-d1);
        }
    }
   
    else if (_digitalOption) {
        if (_digitalOption->GetOptionType() == EuropeanDigitalOption::Call) {
            return std::exp(-r * T) * N(d2);
        } else {
            return std::exp(-r * T) * N(-d2);
        }
    }
    else {
        throw std::invalid_argument("Invalid option type");
    }
}

double BlackScholesPricer::delta() const {
   double T, K;
    if (_option) {
        T = _option->getExpiry();
        K = _option->_strike;
    }
    // Si l'option est de type Digital
    else if (_digitalOption) {
       
        T = _digitalOption->getExpiry();
        K = _digitalOption->_strike;
    }
    double S = _assetPrice;
    double r = _interestRate;
    double sigma = _volatility;
 
    double d1 = (log(S/K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
 
    if (_option) {
        if (_option->GetOptionType() == EuropeanVanillaOption::Call){
            return N(d1);
        } else {
            return N(d1) - 1.0;
        }
    }
    else if (_digitalOption) {
        if (_digitalOption->GetOptionType() == EuropeanDigitalOption::Call) {
            return std::exp(-r * T) * N(d1) / (S * sigma * std::sqrt(T));
        } else {
            return -std::exp(-r * T) * N(-d1) / (S * sigma * std::sqrt(T));
        }
    } else {
        throw std::invalid_argument("Unsupported option type for delta calculation");
    }
}

BlackScholesPricer::~BlackScholesPricer() {}