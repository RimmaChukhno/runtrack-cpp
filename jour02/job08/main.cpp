#include "classes.hpp"
#include <iostream>

int main()
{
    // Création de pingouins avec des shared_ptr
    auto p1 = std::make_shared<Pingouin>("Emperor", 10.0, 2.5);
    auto p2 = std::make_shared<Pingouin>("King", 8.0, 2.0);
    auto p3 = std::make_shared<Pingouin>("Gentoo", 9.0, 2.8);

    // Création de liens d'amitié
    std::cout << "=== Création des liens d'amitié ===\n";
    p1->ajouterAmi(p2);
    p1->ajouterAmi(p3);
    p2->ajouterAmi(p1);
    p3->ajouterAmi(p1);

    // Affichage des amis
    std::cout << "\n=== Liste des amis ===\n";
    p1->listerAmis();
    p2->listerAmis();
    p3->listerAmis();

    // Test de suppression d'un ami
    std::cout << "\n=== Après suppression d'un ami ===\n";
    p1->retirerAmi(p2);
    p1->listerAmis();

    // Test avec un ami qui disparaît
    {
        auto p4 = std::make_shared<Pingouin>("Rockhopper", 8.5, 2.3);
        p1->ajouterAmi(p4);
        std::cout << "\n=== Ajout d'un ami temporaire ===\n";
        p1->listerAmis();
    } // p4 est détruit ici

    // Nettoyage des amis expirés
    std::cout << "\n=== Après nettoyage des amis expirés ===\n";
    p1->nettoyerAmisExpires();
    p1->listerAmis();

    return 0;
}