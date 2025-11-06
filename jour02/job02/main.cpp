#include "classes.hpp"
#include <iostream>

int main()
{
    // Création d'un pingouin
    Pingouin p1("Emperor", 10.0, 2.5);

    // Test des méthodes de base
    p1.sePresenter();
    p1.nage();
    p1.marche();

    // Test du copy constructor
    Pingouin p2(p1);
    std::cout << "\nPingouin copié :\n";
    p2.sePresenter();

    // Test des setters de vitesse
    std::cout << "\nModification des vitesses :\n";
    p2.setVitesseGlisse(7.0);
    p2.setVitesseNage(12.0);
    p2.setVitesseMarche(3.0);
    std::cout << "Nouvelle vitesse de glisse : " << p2.getVitesseGlisse() << " m/s\n";
    p2.sePresenter();

    return 0;
}