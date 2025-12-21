#ifndef MT_HPP
#define MT_HPP

#include <random>

using namespace std;

class MT {

    private:

        static MT* instance; // Pointeur pour l'instance unique
        static mt19937 generator; // Générateur de nombres aléatoires

        MT() = default; // Constructeur privé 
 
    public:

        // Méthodes pour générer des nombres aléatoires
        static double rand_unif();
        static double rand_norm();

        static MT& getInstance() {
            static MT instance; 
            return instance;
        }

        // Suppression des méthodes de copie pour garantir un singleton
        MT(const MT&) = delete;
        MT& operator=(const MT&) = delete;
};

#endif