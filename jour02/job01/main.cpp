#include "classes.hpp"
#include <iostream>

int main()
{
    // Création de quelques pingouins
    Pingouin p1("Emperor", 10.0, 2.5);
    Pingouin p2("King", 8.0, 2.0);

    // Test des méthodes
    p1.sePresenter();
    p1.nage();
    p1.marche();

    std::cout << "\n--- Copie d'un pingouin ---\n";
    Pingouin p3(p1); // Utilisation du copy constructor
    p3.sePresenter();

    std::cout << "\n--- Test des vitesses ---\n";
    p1.setVitesseNage(12.0);
    p1.setVitesseMarche(3.0);
    p1.setVitesseGlisse(6.0);
    p1.sePresenter();

    std::cout << "\n--- Temps de parcours ---\n";
    Pingouin::afficherTemps();

    return 0;
}