#ifndef ENEMY_FACTORY_HPP
#define ENEMY_FACTORY_HPP

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <memory>

// Base class
class Enemy
{
public:
    virtual ~Enemy() = default;
    virtual void attack() = 0;
};

// Derived classes
class Goblin : public Enemy
{
public:
    void attack() override
    {
        std::cout << "Goblin attacks with a dagger!" << std::endl;
    }
};

class Ogre : public Enemy
{
public:
    void attack() override
    {
        std::cout << "Ogre attacks with a club!" << std::endl;
    }
};

class Dragon : public Enemy
{
public:
    void attack() override
    {
        std::cout << "Dragon attacks with fire breath!" << std::endl;
    }
};

// Factory class
class EnemyFactory
{
private:
    std::map<std::string, std::function<std::unique_ptr<Enemy>()>> enemyCreators;

public:
    EnemyFactory()
    {
        // Initialize the map with enemy creators
        enemyCreators["goblin"] = []()
        { return std::make_unique<Goblin>(); };
        enemyCreators["ogre"] = []()
        { return std::make_unique<Ogre>(); };
        enemyCreators["dragon"] = []()
        { return std::make_unique<Dragon>(); };
    }

    std::unique_ptr<Enemy> createEnemy(const std::string &type)
    {
        auto it = enemyCreators.find(type);
        if (it != enemyCreators.end())
        {
            return it->second();
        }
        return nullptr;
    }
};

#endif // ENEMY_FACTORY_HPP