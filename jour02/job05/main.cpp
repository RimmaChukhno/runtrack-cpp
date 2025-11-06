#include "classes.hpp"
#include <iostream>

int main()
{
    // Création de pingouins avec différentes vitesses
    Pingouin p1("Emperor", 10.0, 2.5);
    Pingouin p2("King", 8.0, 3.0);
    Pingouin p3("Gentoo", 9.0, 2.8);

    // Configuration initiale des vitesses de glisse
    p1.setVitesseGlisse(6.0);
    p2.setVitesseGlisse(5.5);
    p3.setVitesseGlisse(7.0);

    // Affichage des temps initiaux (déjà triés)
    std::cout << "=== Classement initial ===\n";
    Pingouin::afficherTemps();

    // Modification des vitesses pour voir le tri automatique
    std::cout << "\n=== Après modification des vitesses ===\n";
    p2.setVitesseNage(12.0);  // Amélioration de la vitesse de nage
    p2.setVitesseGlisse(8.0); // Amélioration de la vitesse de glisse
    Pingouin::afficherTemps();

    // Ajout d'un nouveau pingouin
    std::cout << "\n=== Après ajout d'un nouveau pingouin ===\n";
    Pingouin p4("Adelie", 11.0, 3.2); // Très rapide
    p4.setVitesseGlisse(7.5);
    Pingouin::afficherTemps();

    return 0;
}