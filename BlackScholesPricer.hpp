#ifndef BLACKSCHOLESPRICER_HPP
#define BLACKSCHOLESPRICER_HPP
#include <cmath>
#include <algorithm>
#include "EuropeanVanillaOption.hpp"
#include "CallOption.hpp"
#include "PutOption.hpp"
#include "EuropeanDigitalCallOption.hpp" 
#include "EuropeanDigitalPutOption.hpp"  

using namespace std;

class BlackScholesPricer {

    private:

        EuropeanVanillaOption* _option; // Option européenne
        EuropeanDigitalOption* _digitalOption; // Option digitale

        double _assetPrice; // Prix de l'actif
        double _interestRate; // Taux d'intérêt
        double _volatility; // Volatilité
        int _numPaths; // Nombre de chemins générés
        double _priceEstimate; // Estimation du prix de l'option

        // Fonction de répartition d'une loi normale centrée réduite
        double cumulativeNormal(double x) const {
            return 0.5*erfc(-x/sqrt(2.0));
        }
 
    public:

        BlackScholesPricer(EuropeanVanillaOption* _option, double _asset_price, double _interestRate, double _volatility); // Constructeur

        BlackScholesPricer(EuropeanDigitalOption* _option, double _asset_price, double _interestRate, double _volatility); // Constructeur

        friend class EuropeanVanillaOption; 

        friend class EuropeanDigitalOption;

        double operator()() const; // Opérateur d'appel
 
        double delta() const; // Calcul du delta

        virtual ~BlackScholesPricer(); // Destructeur

        double price() const; // Calcul du prix de l'option

};


#endif 