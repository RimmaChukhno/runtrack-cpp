#include "classes.hpp"
#include <iostream>
#include <iomanip>

int main()
{
    // Création d'un pingouin
    auto p1 = std::make_shared<Pingouin>("Emperor", 10.0, 2.5);

    // Ajout de plusieurs temps de glisse
    std::cout << "=== Ajout de temps de glisse ===\n";
    p1->ajouterTempsGlisse(12.5); // Temps moyen
    p1->ajouterTempsGlisse(10.8); // Meilleur temps
    p1->ajouterTempsGlisse(13.2); // Pire temps
    p1->ajouterTempsGlisse(11.5);
    p1->ajouterTempsGlisse(12.0);

    // Affichage des temps (automatiquement triés)
    std::cout << "\n=== Tous les temps de glisse ===\n";
    p1->afficherTempsGlisse();

    // Affichage des statistiques
    std::cout << "\n=== Statistiques ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Meilleur temps: " << p1->getMeilleurTemps() << " secondes\n";
    std::cout << "Pire temps: " << p1->getPireTemps() << " secondes\n";
    std::cout << "Temps moyen: " << p1->getMoyenneTemps() << " secondes\n";

    // Suppression du meilleur temps
    std::cout << "\n=== Après suppression du meilleur temps ===\n";
    p1->supprimerMeilleurTemps();
    p1->afficherTempsGlisse();

    // Suppression du pire temps
    std::cout << "\n=== Après suppression du pire temps ===\n";
    p1->supprimerPireTemps();
    p1->afficherTempsGlisse();

    // Test du copy constructor avec les temps
    std::cout << "\n=== Temps du pingouin copié ===\n";
    Pingouin p2(*p1);
    p2.afficherTempsGlisse();

    return 0;
}