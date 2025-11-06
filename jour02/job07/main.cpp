#include "classes.hpp"
#include <iostream>

int main()
{
    // Création d'un pingouin
    Pingouin p1("Emperor", 10.0, 2.5);

    // Test des compétences par défaut
    std::cout << "=== Compétences initiales ===\n";
    p1.listerCompetences();

    // Ajout de nouvelles compétences
    std::cout << "\n=== Ajout de compétences ===\n";
    p1.ajouterCompetence("Pêche", 8);
    p1.ajouterCompetence("Plongée", 7);
    p1.ajouterCompetence("Glisse", 6);
    p1.listerCompetences();

    // Modification d'une compétence
    std::cout << "\n=== Modification d'une compétence ===\n";
    p1.modifierCompetence("Pêche", 9);
    p1.listerCompetences();

    // Suppression d'une compétence
    std::cout << "\n=== Suppression d'une compétence ===\n";
    p1.supprimerCompetence("Glisse");
    p1.listerCompetences();

    // Test du copy constructor avec les compétences
    std::cout << "\n=== Test de la copie des compétences ===\n";
    Pingouin p2(p1);
    p2.listerCompetences();

    return 0;
}