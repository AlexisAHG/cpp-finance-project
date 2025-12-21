#ifndef OPTION_HPP
#define OPTION_HPP

#include<iostream>

using namespace std;

class Option{

    private :

        double _expiry; // Échéance de l'option
 
    public :

        Option(double expiry); // Constructeur

        virtual double getExpiry() const; // Méthode pour obtenir l'échéance
        virtual double payoff(double uPrice) const=0; // Méthode pour obtenir le payoff
        virtual double payoffPath(const vector<double>& path) const; // Méthode pour obtenir le payoff d'un chemin
        virtual bool isAsianOption() const { return false; } // Méthode pour vérifier si l'option est asiatique
        virtual bool isAmericanOption() const {return false;} // Méthode pour vérifier si l'option est américaine

        virtual ~Option(); // Destructeur
}; 

#endif // OPTION_HPP