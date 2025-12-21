#ifndef CRRPRICER_HPP
#define CRRPRICER_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "BinaryTree.hpp" 
#include "Option.hpp"
#include "MT.hpp"

using namespace std;

class CRRPricer {

    private:

        Option* _option; // Pointeur vers l'option
        int _depth; // Profondeur de l'arbre
        double _asset_price; // Prix de l'actif 
        double _up; // Facteur d'augmentation
        double _down; // Facteur de diminution
        double _interest_rate; // Taux d'intérêt
        BinaryTree<double> _tree; // Arbre binaire pour les prix
        BinaryTree<bool> _exercise; // Arbre binaire pour la politique d'exercice
        bool _computed; // Booléen pour vérifier si les prix ont été calculés
        bool _use_closed_form; 
        double _risk_neutral_prob; 

        void check_arbitrage(); 

    public:
 
        CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate,bool use_closed_form=false); // Constructeur 

        bool getExercise(int n, int i) const; // Méthode pour obtenir la politique d'exercice
 
        CRRPricer(Option* option, int depth, double asset_price, double r, double volatility); // Nouveau constructeur avec calcul de `up`, `down`, `interest_rate` selon Black-Scholes 

        void compute(); // Méthode pour calculer les prix de l'option
        double computeAmericanPrice(); // Méthode pour calculer le prix d'une option américaine
        double operator()(bool closed_form = false); // Surcharge de l'opérateur 
        double closed_form_formula() const; // Méthode pour calculer le prix d'une option européenne avec la formule fermée
        double binomial_coefficient(int n, int k) const; // Méthode pour calculer le coefficient binomial

};
 
#endif // CRRPRICER_HPP