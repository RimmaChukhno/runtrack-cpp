#include "classes.hpp"
#include <iostream>

int main()
{
    // Création de pingouins qui seront automatiquement ajoutés à la colonie
    Pingouin p1("Emperor", 10.0, 2.5);
    Pingouin p2("King", 8.0, 2.0);

    // Affichage de la colonie initiale
    std::cout << "=== Colonie initiale ===\n";
    Pingouin::afficherColonie();

    // Test du copy constructor
    {
        std::cout << "\n=== Ajout d'un pingouin copié ===\n";
        Pingouin p3(p1); // Sera automatiquement ajouté à la colonie
        Pingouin::afficherColonie();

        std::cout << "\n=== Le pingouin copié va être détruit ===\n";
    } // p3 est détruit ici

    // Vérification de la colonie après destruction
    std::cout << "\n=== Colonie finale ===\n";
    Pingouin::afficherColonie();

    return 0;
}