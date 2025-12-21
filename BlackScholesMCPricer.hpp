#ifndef BLACKSCHOLESMCPRICER_HPP
#define BLACKSCHOLESMCPRICER_HPP
#include "Option.hpp"
#include <vector>

using namespace std;

class BlackScholesMCPricer {

    private:

        Option* _option; // Option à pricer
        double _initialPrice, _interestRate, _volatility; // Paramètres du modèle
        int _numPaths; // Nombre de chemins générés
        double _priceEstimate; // Estimation du prix de l'option
 
    public:
 
        BlackScholesMCPricer(Option* option, double initialPrice, double interestRate, double volatility); // Constructeur

        int getNbPaths() const {return _numPaths;} // Accessibilité du nombre de chemins générés

        void generate(int nb_paths); // Générer les chemins

        double operator()() const; // Opérateur d'appel

        vector<double> confidenceInterval() const; // Intervalle de confiance

};

#endif