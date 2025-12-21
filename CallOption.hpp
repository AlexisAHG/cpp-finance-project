#ifndef CALLOPTION_HPP
#define CALLOPTION_HPP
#include "EuropeanVanillaOption.hpp"
#include <algorithm>

using namespace std;

class CallOption : public EuropeanVanillaOption{

    public :
        CallOption(double expiry, double strike); // Constructeur

        double payoff(double uPrice) const override; // Fonction payoff

        optionType GetOptionType() const override; // Fonction GetOptionType qui retourne le type de l'option (call ou put)

        bool isAmericanOption() const override { // Fonction qui permet de savoir si l'option est de type américaine
            return false;
        }
        
        ~CallOption(); // Destructeur
};

#endif 