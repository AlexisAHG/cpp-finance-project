#ifndef ASIANCALLOPTION_HPP
#define ASIANCALLOPTION_HPP
#include "AsianOption.hpp"

using namespace std;

class AsianCallOption : public AsianOption {

    private:

        double _strike; // Prix d'exercice

    public:

        AsianCallOption(const vector<double>& timeSteps, double strike); // Constructeur

        double payoff(double S) const override; // Payoff d'une option call

};

#endif