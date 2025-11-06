#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <algorithm>

struct Vector2d
{
    double x{0}, y{0};
    double dist(const Vector2d &o) const
    {
        double dx = x - o.x, dy = y - o.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

class GameObject
{
public:
    Vector2d pos;
    virtual ~GameObject() = default;
    virtual void update() = 0;
    virtual void draw() const = 0;
    virtual bool isAlive() const { return true; }
};

class Character : public GameObject
{
public:
    Character(std::string n, int hp, Vector2d p) : name(std::move(n)), hp(hp) { pos = p; }
    void draw() const override
    {
        std::cout << name << " HP=" << hp << " at (" << pos.x << "," << pos.y << ")\n";
    }
    bool isAlive() const override { return hp > 0; }
    void damage(int d)
    {
        hp -= d;
        if (hp < 0)
            hp = 0;
    }
    const std::string &getName() const { return name; }
    int getHp() const { return hp; }

protected:
    std::string name;
    int hp;
};

class Enemy : public Character
{
public:
    Enemy(std::string n, int hp, Vector2d p) : Character(std::move(n), hp, p) {}
    void update() override
    {
        if (target)
        {
            double d = pos.dist(target->pos);
            if (d > 1.0)
            {
                pos.x += (target->pos.x - pos.x) / d * 0.4;
                pos.y += (target->pos.y - pos.y) / d * 0.4;
            }
        }
    }
    void setTarget(GameObject *t) { target = t; }

private:
    GameObject *target{nullptr};
};

class Player : public Character
{
public:
    Player(std::string n, int hp, Vector2d p) : Character(std::move(n), hp, p) {}
    void update() override {} // player moves via commands
    void attack(Enemy &e) { e.damage(2); }
};

int main()
{
    Player player("Hero", 20, {0, 0});
    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Enemy>("Goblin", 5, Vector2d{5, 0}));
    enemies.push_back(std::make_unique<Enemy>("Orc", 8, Vector2d{6, 2}));

    int turn = 0;
    while (player.isAlive() && !enemies.empty() && turn < 20)
    {
        std::cout << "--- Turn " << turn << " ---\n";
        // player attacks first: attack first alive enemy
        for (auto &e : enemies)
        {
            if (e->isAlive())
            {
                player.attack(*e);
                std::cout << "Player attacked " << e->getName() << " hp=" << e->getHp() << "\n";
                break;
            }
        }
        // remove dead
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const std::unique_ptr<Enemy> &e)
                                     { return !e->isAlive(); }),
                      enemies.end());
        // enemies update
        for (auto &e : enemies)
        {
            e->setTarget(&player);
            e->update();
            e->draw();
            if (e->pos.dist(player.pos) <= 1.0)
            {
                player.damage(1);
                std::cout << "Enemy hits player! Player HP=" << player.getHp() << "\n";
            }
        }
        turn++;
    }
    std::cout << "Game over: player hp=" << player.getHp() << " enemies remaining=" << enemies.size() << "\n";
    return 0;
}
