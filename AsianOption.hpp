#ifndef ASIANOPTION_HPP
#define ASIANOPTION_HPP
#include "Option.hpp" 
#include <vector>

using namespace std;

class AsianOption : public Option {

    private:

        vector<double> _timeSteps;

    public:

        AsianOption(const std::vector<double>& timeSteps); // Constructeur

        vector<double> getTimeSteps() const; // Méthode pour obtenir les instants de temps associés à l'option

        double payoffPath(const vector<double>& path) const override; // Méthode pour calculer le payoff d'une option asiatique (calcul de la moyenne des prix de l'actif au cours du temps)

        bool isAsianOption() const override { return true; } // Méthode pour savoir si l'option est asiatique afin de savoir quelle méthode utiliser

        int getNumTimeSteps() const; // Méthode pour obtenir le nombre d'instants de temps associés à l'option 
};

#endif