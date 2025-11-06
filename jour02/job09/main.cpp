#include "classes.hpp"
#include <iostream>

int main()
{
    // Création d'un pingouin
    auto p1 = std::make_shared<Pingouin>("Emperor", 10.0, 2.5);

    // Ajout d'événements au journal
    std::cout << "=== Ajout d'événements au journal ===\n";
    p1->ajouterEvenement("2025-11-01", "Premier jour de pêche de la saison");
    p1->ajouterEvenement("2025-11-02", "Découverte d'un nouveau territoire");
    p1->ajouterEvenement("2025-11-03", "Rencontre avec d'autres pingouins");

    // Affichage du journal
    std::cout << "\n=== Journal initial ===\n";
    p1->afficherJournal();

    // Modification d'un événement
    std::cout << "\n=== Après modification d'un événement ===\n";
    p1->modifierEvenement("2025-11-02", "Exploration d'un nouveau territoire glacé");
    p1->afficherJournal();

    // Suppression d'un événement
    std::cout << "\n=== Après suppression d'un événement ===\n";
    p1->supprimerEvenement("2025-11-01");
    p1->afficherJournal();

    // Test du copy constructor avec le journal
    std::cout << "\n=== Journal du pingouin copié ===\n";
    Pingouin p2(*p1);
    p2.afficherJournal();

    return 0;
}