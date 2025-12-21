#include "BinaryTree.hpp"

using namespace std;

// Le constructeur par défaut initialise la profondeur à 0
template <typename T>
BinaryTree<T>::BinaryTree() : _depth(0) {}

template <typename T>
BinaryTree<T>::BinaryTree(int depth) : _depth(depth) {
    setDepth(depth); 
}

// Définit la profondeur de l'arbre 
template<class T>
void BinaryTree<T>::setDepth(int N) {
    if (_depth == 0) { // Si la pronfondeur est initialisée à 0
        _tree.resize(N + 1); // Redimensionne pour contenir les niveaux de 0 à N
        for (int i = 0; i <= N; i++) {
            std::vector<T> vec; // Crée un vecteur pour stocker les noeuds du niveau actuel
            for (int j = 0; j <= i; j++) {
                T obj = T(); // Initialise chaque noeud à sa valeur par défaut
                vec.push_back(obj);
            }
            _tree[i] = vec; // Ajoute le niveau à l'arbre
        }
        _depth = N; // Met à jour la profondeur de l'arbre
    } else { // Si l'arbre a déjà une profondeur
        if (N < _depth) _tree.resize(N + 1); // Réduit la taille si N est plus petit que la pronfondeur actuelle
        else if (N > _depth) { // Ajoute des niveaux si N est plus grand
            for (int i = _depth + 1; i <= N; i++) {
                std::vector<T> vec;
                for (int j = 0; j <= i; j++) {
                    T obj = T();
                    vec.push_back(obj);
                }
                _tree.push_back(vec);
            }
        }
        _depth = N; // Met à jour la nouvelle profondeur
    }
}

template <typename T>
void BinaryTree<T>::setNode(int level, int index, T value) {
    if (level < 0 || level > _depth) { // Vérifie si le niveau est dans l'arbre
        cout << "Level out of range." << endl;
        return;
    }
    if (index < 0 || index >= _tree[level].size()) { // Vérifie si l'index est dans l'arbre
        cout << "Index out of range." << endl;
        return;
    }
    _tree[level][index] = value; // Définit la valeur du noeud
}

template <typename T>
T BinaryTree<T>::getNode(int level, int index) const {
    if (level < 0 || level > _depth) { 
        cout << "Level out of range." << endl;
        return T(); 
    }
    if (index < 0 || index >= _tree[level].size()) {
        cout << "Index out of range." << endl;
        return T();
    }
    return _tree[level][index]; // Retourne la valeur du noeud
}

template<typename T>
void BinaryTree<T>::display() const {
    int width = 3; // Largeur entre la valeur des noeuds pour avoir de l'espace pour les grands nombres
    for (int i = 0; i <= _depth; i++) { // Parcourt chaque ligne
        for (int j = 0; j <= i; j++) { // Parcourt chaque "colonne" 
            cout << setw(width) << _tree[i][j] << "   "; // Affiche la valeur du noeud à l'emplacement actuel
        }
        cout << endl; // On passe à la ligne pour le niveau suivant
    }
    cout << endl;
    display2(); // 2ème méthode appelée dans la 1ère pour éviter d'avoir à appeler 2 méthodes différentes dès lors que l'on veut afficher l'arbre
}

template<typename T>
void BinaryTree<T>::display2() const {
    int maxDepth = _depth; // Profondeur maximale de l'arbre
    int width = 4; // Largeur pour chaque noeud
    int maxWidth = (1 << (maxDepth - 1)) * width; // Largeur totale pour le dernier niveau ((1<<(maxDepth-1)) calcule le nombre de noeuds du dernier niveau)
    int initialSpace = maxWidth / 4; // Espacement initial avant les nœuds

    for (int i = 0; i < maxDepth; ++i) { // Parcourt chaque niveau
        // Ajoute l'espacement initial avant les nœuds
        cout << setw(initialSpace) << "";
        for (int j = 0; j < _tree[i].size(); ++j) {
            cout << setw(width) << _tree[i][j];
        }
        cout << endl;

        // Affiche les branches pour connecter les nœuds
        if (i < maxDepth - 1) {
            cout << setw(initialSpace + 1) << "";
            for (int j = 0; j < i + 1; ++j) {
                cout << setw(width / 2) << "/" << setw(width / 2) << "\\";
            }
            cout << endl;
        }
        initialSpace -= 2; // Réduit l'espacement pour le niveau suivant
    }
    cout << endl;
}

template class BinaryTree<int>;
template class BinaryTree<double>;
template class BinaryTree<bool>;