#ifndef ASIANPUTOPTION_HPP
#define ASIANPUTOPTION_HPP
#include "AsianOption.hpp"

using namespace std;

class AsianPutOption : public AsianOption {

    private:

        double _strike; // Prix d'exercice

    public:

        AsianPutOption(const vector<double>& timeSteps, double strike); // Constructeur

        double payoff(double S) const override; // Payoff d'une option put

};

#endif