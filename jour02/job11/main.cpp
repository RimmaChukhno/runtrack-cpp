#include "classes.hpp"
#include <iostream>

int main()
{
    // Création d'un pingouin
    auto p1 = std::make_shared<Pingouin>("Emperor", 10.0, 2.5);

    // Ajout de lieux de pêche
    std::cout << "=== Ajout de lieux de pêche ===\n";
    p1->ajouterLieuPeche("Baie des Phoques");
    p1->ajouterLieuPeche("Récif Glacé");
    p1->ajouterLieuPeche("Fosse Profonde");
    p1->ajouterLieuPeche("Banc de Krill");

    // Affichage des lieux de pêche
    std::cout << "\n=== Lieux de pêche connus ===\n";
    p1->afficherLieuxPeche();

    // Vérification d'un lieu
    std::string lieuTest = "Récif Glacé";
    std::cout << "\n=== Vérification de lieu ===\n";
    if (p1->connaitLieuPeche(lieuTest))
    {
        std::cout << p1->getNom() << " connaît le lieu: " << lieuTest << std::endl;
    }
    else
    {
        std::cout << p1->getNom() << " ne connaît pas le lieu: " << lieuTest << std::endl;
    }

    // Retrait d'un lieu
    std::cout << "\n=== Après retrait d'un lieu ===\n";
    p1->retirerLieuPeche("Baie des Phoques");
    p1->afficherLieuxPeche();

    // Affichage du nombre total de lieux
    std::cout << "\nNombre total de lieux de pêche connus: "
              << p1->getNombreLieuxPeche() << std::endl;

    // Test du copy constructor
    std::cout << "\n=== Lieux de pêche du pingouin copié ===\n";
    Pingouin p2(*p1);
    p2.afficherLieuxPeche();

    return 0;
}