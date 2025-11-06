#include "classes.hpp"
#include <iostream>

int main()
{
    // Initialisation des lieux de rencontre
    Pingouin::ajouterLieuRencontre("Glacier Blanc");
    Pingouin::ajouterLieuRencontre("Lac Gelé");
    Pingouin::ajouterLieuRencontre("Baie des Phoques");

    // Création de pingouins
    Pingouin p1("Emperor", 10.0, 2.5);
    Pingouin p2("King", 8.0, 2.0);

    // Ajout de compétences
    p1.ajouterCompetence("Pêche", 8);
    p1.ajouterCompetence("Plongée", 7);
    p2.ajouterCompetence("Glisse", 9);
    p2.ajouterCompetence("Pêche", 6);

    // Ajout d'amis
    auto p1_ptr = std::make_shared<Pingouin>(p1);
    auto p2_ptr = std::make_shared<Pingouin>(p2);
    p1.ajouterAmi(p2_ptr);
    p2.ajouterAmi(p1_ptr);

    // Ajout d'événements au journal
    p1.ajouterEvenement("2025-11-04", "Premier plongeon de la saison");
    p2.ajouterEvenement("2025-11-04", "Découverte d'un nouveau lieu de pêche");

    // Ajout de temps de glisse
    p1.ajouterTempsGlisse(12.5);
    p1.ajouterTempsGlisse(11.8);
    p1.ajouterTempsGlisse(13.2);

    // Configuration des lieux de pêche pour le treasure hunt
    Pingouin::ajouterLieuPecheMeetup("Glacier Blanc", "Zone Profonde");
    Pingouin::ajouterLieuPecheMeetup("Lac Gelé", "Trou de Pêche");

    // Tests des fonctionnalités
    std::cout << "=== Lieux de rencontre ===\n";
    Pingouin::afficherLieuxRencontre();

    std::cout << "\n=== Compétences des pingouins ===\n";
    p1.listerCompetences();
    p2.listerCompetences();

    std::cout << "\n=== Journal des pingouins ===\n";
    p1.listerEvenements();
    p2.listerEvenements();

    std::cout << "\n=== Temps de glisse ===\n";
    p1.afficherTempsGlisse();

    std::cout << "\n=== Treasure Hunt ===\n";
    p1.chercherPoisson("Glacier Blanc");
    p2.chercherPoisson("Lac Gelé");

    return 0;
}