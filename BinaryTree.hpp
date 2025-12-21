#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

using namespace std;    

template<typename T>
 
class BinaryTree {

    private: 

        int _depth; // Profondeur de l'arbre
        std::vector<std::vector<T> > _tree; // Arbre binaire
     

    public:

        BinaryTree(); // Constructeur par défaut
        BinaryTree(int depth); // Constructeur avec une profondeur donnée

        void setDepth(int depth); // Méthode pour définir la profondeur de l'arbre
        void setNode(int level, int index, T value); // Méthode pour définir la valeur d'un noeud
        T getNode(int level, int index) const; // Méthode pour obtenir la valeur d'un noeud
        void display() const; // 1ère méthode pour afficher l'arbre
        void display2() const; // 2ème méthode pour afficher l'arbre (pyramide)

};


#endif // BINARYTREE_HPP