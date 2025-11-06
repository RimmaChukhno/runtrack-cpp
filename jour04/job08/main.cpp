#include <iostream>
#include "enemy_factory.hpp"

int main()
{
    std::cout << "Testing EnemyFactory:\n";

    EnemyFactory factory;

    // Create and test each enemy type
    auto goblin = factory.createEnemy("goblin");
    auto ogre = factory.createEnemy("ogre");
    auto dragon = factory.createEnemy("dragon");

    if (goblin)
    {
        std::cout << "Goblin: ";
        goblin->attack();
    }

    if (ogre)
    {
        std::cout << "Ogre: ";
        ogre->attack();
    }

    if (dragon)
    {
        std::cout << "Dragon: ";
        dragon->attack();
    }

    // Try invalid enemy type
    auto invalid = factory.createEnemy("invalid");
    if (!invalid)
    {
        std::cout << "Could not create invalid enemy type" << std::endl;
    }

    return 0;
}