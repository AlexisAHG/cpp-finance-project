#ifndef EUROPEANVANILLAOPTION_HPP
#define EUROPEANVANILLAOPTION_HPP
#include "Option.hpp"
#include <stdexcept>

using namespace std;

class BlackScholesPricer;

class EuropeanVanillaOption : public Option{
    
    protected :

        double _strike; // Prix d'exercice de l'option

    public :
        
        enum optionType{Call, Put}; // Enumération pour le type d'option

        EuropeanVanillaOption(double expiry, double strike); // Constructeur

        virtual double getStrike() const; // Méthode pour obtenir le prix d'exercice
        virtual optionType GetOptionType() const=0; // Méthode pour obtenir le type d'option

        ~EuropeanVanillaOption(); // Destructeur

        friend class BlackScholesPricer;
 
};
 
#endif 