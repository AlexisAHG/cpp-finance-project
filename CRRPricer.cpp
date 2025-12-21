#include "CRRPricer.hpp"
#include "Option.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;

double POW(double x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    if (n % 2 == 0) {
        double y = POW(x, n / 2);
        return y * y;
    } else {
        return x * POW(x, n - 1);
    }
}

// Constructeur pour une option européenne
CRRPricer::CRRPricer(Option* _option, int _depth, double _asset_price, double _up, double _down, double _interest_rate, bool _use_closed_form)
    : _option(_option), _depth(_depth), _asset_price(_asset_price), _up(_up), _down(_down), _interest_rate(_interest_rate), _use_closed_form(_use_closed_form), _computed(false) {
    if (_down < _interest_rate && _interest_rate < _up) {
        _tree.setDepth(_depth); // Définir la profondeur de l'arbre
        _exercise.setDepth(_depth); // Définir la profondeur de l'arbre d'exercice
    }
    if (_option->isAsianOption()){
        cout << "Asian options not supported in CRRPricer" << endl;
    }
}

// Constructeur pour une option américaine (avec les paramètres de Black-Scholes)
CRRPricer::CRRPricer(Option* _option, int _depth, double _asset_price, double r, double volatility)
    : _option(_option), _depth(_depth), _asset_price(_asset_price) {
  
    double T=_option->getExpiry(); // Durée de vie de l'option
    double h = T / _depth; // Intervalle de temps entre les étapes de l'arbre binomial

    _interest_rate = std::exp(r * h) - 1; 
    _up = std::exp(volatility * std::sqrt(h)) - 1; 
    _down = -_up;  
    _tree.setDepth(_depth); 
    _exercise.setDepth(_depth); 

    if (!(_down < _interest_rate && _interest_rate < _up)) {
        cout << "Arbitrage opportunity detected: ensure that _down < _interest_rate < _up." << endl;
    }

    double q = (_interest_rate - _down) / (_up - _down); // Calcul de la probabilité neutre au risque (probabilité de montée)
}

// Vérification de la condition d'arbitrage
void CRRPricer::check_arbitrage() {
    if (_up <= 1.0 || _down >= 1.0 || _up <= _down) {
        cout << "Arbitrage condition violated" << endl;  
    }
}

void CRRPricer::compute() {
    if (_option->isAmericanOption()) {
        computeAmericanPrice(); // Si l'option est américaine, utiliser une méthode différente
        return;
    }
    
    // Calcul de la probabilité neutre au risque
    double q = (_interest_rate - _down) / (_up - _down); 

    // Étape 1 : Initialisation des prix des actifs et des payoffs des options à maturité
    for (int i = 0; i <= _depth; ++i) {
        double stock_price = _asset_price * POW(1 + _up, i) * POW(1 + _down, _depth - i); 
        double payoff = _option->payoff(stock_price);  
        _tree.setNode(_depth, i, payoff);  
    }

    // Étape 2 : Calcul des valeurs de l'option aux nœuds précédents (méthode de régression)
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double _up_value = _tree.getNode(n + 1, i + 1);
            double _down_value = _tree.getNode(n + 1, i);
            
            double discounted_value = (q * _up_value + (1 - q) * _down_value) / (1 + _interest_rate);
            _tree.setNode(n, i, discounted_value); 
        }
    }
    _computed = true;  // Indiquer que le calcul est terminé
}

// Opérateur de fonction permettant de calculer le prix de l'option avec ou sans la formule fermée
double CRRPricer::operator()(bool _use_closed_form) {
    if (_use_closed_form) {
        return closed_form_formula();  // Utilise la formule fermée pour évaluer le prix
    } else {
        compute();  // Sinon, effectue le calcul via l'arbre binomial
        return _tree.getNode(0, 0);
    }
}

double CRRPricer::closed_form_formula() const {
    double q = (_interest_rate - _down) / (_up - _down); 
    double _option_price = 0.0;

    // Facteur d'actualisation pour ramener les payoffs à la valeur actuelle
    double discount_factor = 1.0 / POW(1 + _interest_rate, _depth);

    // Somme des termes de la formule fermée, avec les coefficients binomiaux
    for (int i = 0; i <= _depth; ++i) {
        double stock_price = _asset_price * POW(1 + _up, i) * POW(1 + _down, _depth - i);  
        double payoff = _option->payoff(stock_price);  
        double binom_coeff = binomial_coefficient(_depth, i); 
        
        _option_price += binom_coeff * POW(q, i) * POW(1 - q, _depth - i) * payoff;
    }

    // Application du facteur d'actualisation
    _option_price *= discount_factor;
    return _option_price; 
}

double CRRPricer::binomial_coefficient(int n, int k) const {
    if (k > n || k < 0) return 0;  
    if (k == 0 || k == n) return 1; 

    double result = 1;
    for (int i = 1; i <= k; ++i) {
        result = result * (n - i + 1) / i;  // Calcul du coefficient binomial
    }
    return result;  
}

double CRRPricer::computeAmericanPrice() {
    double q = (_interest_rate - _down) / (_up - _down);  

    // Calcul des payoffs de l'option à maturité
    for (int i = 0; i <= _depth; ++i) {
        double stock_price = _asset_price * POW(1 + _up, i) * POW(1 + _down, _depth - i);
        _tree.setNode(_depth, i, _option->payoff(stock_price));
        _exercise.setNode(_depth - 1, i, true);  
    }

    // Backward induction pour l'option américaine
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double stock_price = _asset_price * POW(1 + _up, i) * POW(1 + _down, n - i);
            double intrinsic_value = _option->payoff(stock_price);  
            double _up_value = _tree.getNode(n + 1, i + 1);
            double _down_value = _tree.getNode(n + 1, i);
            double continuation_value = (q * _up_value + (1 - q) * _down_value) / (1 + _interest_rate);  

            if (intrinsic_value > continuation_value) {
                _tree.setNode(n, i, intrinsic_value);  // Exercice anticipé si valeur intrinsèque > continuation
                _exercise.setNode(n, i, true);
            } else {
                _tree.setNode(n, i, continuation_value);  // Sinon, continuation
                _exercise.setNode(n, i, false);
            }
        }
    }
    return _tree.getNode(0, 0);  
}

// Méthode pour vérifier si l'option peut être exercée à un noeud donné
bool CRRPricer::getExercise(int n, int i) const {
    if (n < 0 || n > _depth || i < 0 || i > n) {
        cout << "Invalid node" << endl;  
    }
    return _exercise.getNode(n, i);  
}