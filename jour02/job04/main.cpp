#include "classes.hpp"
#include <iostream>

int main()
{
    // Création de pingouins avec différentes vitesses
    Pingouin p1("Emperor", 10.0, 2.5); // Bon nageur
    Pingouin p2("King", 8.0, 3.0);     // Bon marcheur
    Pingouin p3("Gentoo", 9.0, 2.8);   // Équilibré

    // Configuration des vitesses de glisse
    p1.setVitesseGlisse(6.0);
    p2.setVitesseGlisse(5.5);
    p3.setVitesseGlisse(7.0); // Meilleur en glisse

    // Affichage des caractéristiques
    std::cout << "=== Caractéristiques des pingouins ===\n";
    p1.sePresenter();
    p2.sePresenter();
    p3.sePresenter();

    // Affichage des temps de parcours
    std::cout << "\n=== Résultats de la piste olympique ===\n";
    Pingouin::afficherTemps();

    return 0;
}