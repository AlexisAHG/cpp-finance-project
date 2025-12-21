#ifndef EUROPEANDIGITALOPTION_HPP
#define EUROPEANDIGITALOPTION_HPP
#include "Option.hpp"

using namespace std;

class EuropeanDigitalOption : public Option {
    protected:

        double _strike;

    public:
        enum optionType{Call, Put}; // Enumération pour le type d'option

        EuropeanDigitalOption(double expiry, double strike); // Constructeur

        double getStrike() const {return _strike;} // Getter pour le strike

        virtual double payoff(double uPrice) const=0; // Fonction payoff

        virtual optionType GetOptionType() const=0; // Fonction GetOptionType qui sert à déterminer le type de l'option (call ou put)

        virtual ~EuropeanDigitalOption(); // Destructeur

        friend class BlackScholesPricer;
};
 

#endif // EUROPEANDIGITALOPTION_HPP 