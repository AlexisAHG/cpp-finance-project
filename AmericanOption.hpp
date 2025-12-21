#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP
#include "Option.hpp"

using namespace std;

// Classe de base pour les options américaines
class AmericanOption : public Option {

    public:

        AmericanOption(double expiry); // Constructeur


        bool isAmericanOption() const override; // Indique si c'est une option américaine pour savoir quelle méthode utiliser

};

#endif // AMERICANOPTION_HPP