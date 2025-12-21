#ifndef AMERICANCALLOPTION_HPP
#define AMERICANCALLOPTION_HPP
#include "AmericanOption.hpp"

using namespace std;

class AmericanCallOption : public AmericanOption {

    private:

        double _strike; // Prix d'exercice
 
    public:

        AmericanCallOption(double expiry, double strike); //Constructeur

        double payoff(double stockPrice) const override; // Payoff d'une option call (gain réalisé par le détenteur de l'option si elle est exercée à échéance)
        
};

#endif // AMERICANCALLOPTION_HPP