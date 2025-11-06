#include <iostream>
#include <string>
#include <vector>
#include <memory>
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

class Enemy : public GameObject
{
public:
    Enemy(std::string n, int hp, Vector2d p) : name(std::move(n)), hp(hp) { pos = p; }
    void update() override
    {
        if (target)
        {
            double d = pos.dist(target->pos);
            if (d > 0.0)
            {
                pos.x += (target->pos.x - pos.x) / d * 0.3;
                pos.y += (target->pos.y - pos.y) / d * 0.3;
            }
        }
    }
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
    void setTarget(GameObject *t) { target = t; }

private:
    std::string name;
    int hp;
    GameObject *target{nullptr};
};

// Weapon interface and implementations
class Weapon
{
public:
    virtual ~Weapon() = default;
    virtual void attack(Enemy &target) = 0;
    virtual int getRange() const = 0;
    virtual const char *getName() const = 0;
};

class Bow : public Weapon
{
public:
    void attack(Enemy &target) override { target.damage(1); }
    int getRange() const override { return 4; }
    const char *getName() const override { return "Bow"; }
};

class Spear : public Weapon
{
public:
    void attack(Enemy &target) override { target.damage(2); }
    int getRange() const override { return 2; }
    const char *getName() const override { return "Spear"; }
};

class Sword : public Weapon
{
public:
    void attack(Enemy &target) override { target.damage(4); }
    int getRange() const override { return 1; }
    const char *getName() const override { return "Sword"; }
};

class Player : public GameObject
{
public:
    Player(Vector2d p) : hp(20)
    {
        pos = p;
        weapons.push_back(std::make_unique<Bow>());
        weapons.push_back(std::make_unique<Spear>());
        weapons.push_back(std::make_unique<Sword>());
        currentWeapon = 0;
    }

    void update() override {} // Player moves via commands

    void draw() const override
    {
        std::cout << "Player HP=" << hp << " at (" << pos.x << "," << pos.y
                  << ") with " << weapons[currentWeapon]->getName() << "\n";
    }

    void move(const std::string &dir)
    {
        if (dir == "up")
            pos.y -= 1;
        else if (dir == "down")
            pos.y += 1;
        else if (dir == "left")
            pos.x -= 1;
        else if (dir == "right")
            pos.x += 1;
    }

    void attack(Enemy &e)
    {
        if (pos.dist(e.pos) <= weapons[currentWeapon]->getRange())
        {
            weapons[currentWeapon]->attack(e);
            std::cout << "Attacked with " << weapons[currentWeapon]->getName() << "!\n";
        }
        else
        {
            std::cout << "Target is out of range for " << weapons[currentWeapon]->getName() << "\n";
        }
    }

    void switchWeapon()
    {
        currentWeapon = (currentWeapon + 1) % weapons.size();
        std::cout << "Switched to " << weapons[currentWeapon]->getName() << "\n";
    }

    bool isAlive() const override { return hp > 0; }
    int getHp() const { return hp; }
    void damage(int d)
    {
        hp -= d;
        if (hp < 0)
            hp = 0;
    }

private:
    int hp;
    std::vector<std::unique_ptr<Weapon>> weapons;
    size_t currentWeapon;
};

int main()
{
    Player player({0, 0});
    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Enemy>("Goblin", 5, Vector2d{3, 0}));

    std::string cmd;
    int turn = 0;
    while (player.isAlive() && !enemies.empty())
    {
        // Show game state
        std::cout << "\n=== Turn " << turn << " ===\n";
        player.draw();
        for (const auto &e : enemies)
            e->draw();

        std::cout << "\nCommands: move up/down/left/right | attack | switch | status | quit\n> ";
        if (!(std::cin >> cmd))
            break;

        if (cmd == "move")
        {
            std::string d;
            std::cin >> d;
            player.move(d);
        }
        else if (cmd == "attack")
        {
            if (!enemies.empty())
            {
                player.attack(*enemies.front());
            }
        }
        else if (cmd == "switch")
        {
            player.switchWeapon();
        }
        else if (cmd == "status")
        {
            player.draw();
            std::cout << "Enemies:\n";
            for (const auto &e : enemies)
                e->draw();
        }
        else if (cmd == "quit")
            break;

        // Update enemies
        for (auto &e : enemies)
        {
            if (!e->isAlive())
                continue;
            e->setTarget(&player);
            e->update();
            if (e->pos.dist(player.pos) <= 1.0)
            {
                player.damage(1);
                std::cout << e->getName() << " hits you! HP=" << player.getHp() << "\n";
            }
        }

        // Clean up dead enemies
        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                           [](const std::unique_ptr<Enemy> &e)
                           { return !e->isAlive(); }),
            enemies.end());

        turn++;
    }

    std::cout << "\nGame Over!\n";
    if (player.isAlive())
        std::cout << "You won! " << enemies.size() << " enemies remaining.\n";
    else
        std::cout << "You were defeated!\n";
    return 0;
}
