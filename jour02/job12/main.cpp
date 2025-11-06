#include "classes.hpp"
#include <iostream>

int main()
{
    // Configuration des lieux de pêche et points de rencontre
    Pingouin::ajouterLieuPecheMeetup("Glacier Blanc", "Zone Profonde");
    Pingouin::ajouterLieuPecheMeetup("Glacier Blanc", "Crevasse Glacée");
    Pingouin::ajouterLieuPecheMeetup("Lac Gelé", "Trou de Pêche");
    Pingouin::ajouterLieuPecheMeetup("Baie des Phoques", "Récif Côtier");
    Pingouin::ajouterLieuPecheMeetup("Baie des Phoques", "Fosse aux Poissons");

    // Affichage de tous les lieux de pêche par point de rencontre
    std::cout << "=== Lieux de pêche disponibles ===\n";
    Pingouin::afficherTousLieuxPecheMeetup();

    // Création de pingouins
    auto p1 = std::make_shared<Pingouin>("Emperor", 10.0, 2.5);
    auto p2 = std::make_shared<Pingouin>("King", 8.0, 2.0);

    // Test de chasse
    std::cout << "\n=== Première session de pêche ===\n";
    for (int i = 0; i < 3; ++i)
    {
        p1->chercherPoisson("Glacier Blanc");
        p2->chercherPoisson("Baie des Phoques");
    }

    // Affichage des journaux de pêche
    std::cout << "\n=== Journaux de pêche ===\n";
    p1->afficherJournal();
    std::cout << "\n";
    p2->afficherJournal();

    // Affichage des lieux de pêche découverts
    std::cout << "\n=== Lieux de pêche découverts ===\n";
    p1->afficherLieuxPeche();
    std::cout << "\n";
    p2->afficherLieuxPeche();

    // Test de modification des lieux
    std::cout << "\n=== Après retrait d'un lieu de pêche ===\n";
    Pingouin::retirerLieuPecheMeetup("Glacier Blanc", "Zone Profonde");
    Pingouin::afficherTousLieuxPecheMeetup();

    return 0;
}