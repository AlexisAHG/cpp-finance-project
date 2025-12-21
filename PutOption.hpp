#ifndef PUTOPTION_HPP
#define PUTOPTION_HPP
#include "EuropeanVanillaOption.hpp"
#include <algorithm>

using namespace std;

class PutOption : public EuropeanVanillaOption{

    public :

        PutOption(double expiry, double strike); // Constructeur

        double payoff(double uPrice) const override; // Fonction payoff

        optionType GetOptionType() const override; // Fonction GetOptionType qui sert à déterminer le type de l'option (call ou put)

        bool isAmericanOption() const override { // Fonction qui sert à déterminer si l'option est de type américaine
            return false;
        }

        ~PutOption(); // Destructeur
};

#endif 