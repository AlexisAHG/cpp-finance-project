#ifndef EUROPEANDIGITALPUTOPTION_HPP
#define EUROPEANDIGITALPUTOPTION_HPP
#include "EuropeanDigitalOption.hpp"

using namespace std;

class EuropeanDigitalPutOption : public EuropeanDigitalOption {

    public:

        EuropeanDigitalPutOption(double expiry, double strike); // Constructeur

        optionType GetOptionType() const override;

        double payoff(double z) const override; // Fonction payoff ("override" sert à redéfinir la fonction)

};

#endif // EUROPEANDIGITALPUTOPTION_HPP