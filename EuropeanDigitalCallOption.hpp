#ifndef EUROPEANDIGITALCALLOPTION_HPP
#define EUROPEANDIGITALCALLOPTION_HPP
#include "EuropeanDigitalOption.hpp"

using namespace std;

class EuropeanDigitalCallOption : public EuropeanDigitalOption {

    public:

        EuropeanDigitalCallOption(double expiry, double strike); // Constructeur

        optionType GetOptionType() const override;

        double payoff(double z) const override; // Fonction payoff ("override" permet de redéfinir la fonction)
        
};

#endif // EUROPEANDIGITALCALLOPTION_HPP