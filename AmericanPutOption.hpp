#ifndef AMERICANPUTOPTION_HPP
#define AMERICANPUTOPTION_HPP
#include "AmericanOption.hpp"

using namespace std;

class AmericanPutOption : public AmericanOption {

    private:

        double _strike; // Prix d'exercice

    public:

        AmericanPutOption(double expiry, double strike); // Constructeur

        double payoff(double stockPrice) const override; // Payoff d'une option put
        
};

#endif // AMERICANPUTOPTION_HPP