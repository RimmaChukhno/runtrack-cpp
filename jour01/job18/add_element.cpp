#include <iostream>

void addElement(int *&arr, size_t &taille, int valeur) {
    int *nouveau = new int[taille + 1];
    for (size_t i = 0; i < taille; ++i) nouveau[i] = arr[i];
    nouveau[taille] = valeur;
    delete[] arr;
    arr = nouveau;
    ++taille;
}

int main() {
    size_t taille;
    std::cout << "Entrez la taille initiale du tableau : ";
    if (!(std::cin >> taille) || taille == 0) return 0;

    int *tab = new int[taille];
    std::cout << "Entrez " << taille << " entiers : ";
    for (size_t i = 0; i < taille; ++i) std::cin >> tab[i];

    std::cout << "Tableau avant ajout : ";
    for (size_t i = 0; i < taille; ++i) std::cout << tab[i] << (i+1==taille ? "\n" : " ");

    int val;
    std::cout << "Entrez la valeur à ajouter : ";
    std::cin >> val;
    addElement(tab, taille, val);

    std::cout << "Tableau après ajout : ";
    for (size_t i = 0; i < taille; ++i) std::cout << tab[i] << (i+1==taille ? "\n" : " ");

    delete[] tab;
    return 0;
}
