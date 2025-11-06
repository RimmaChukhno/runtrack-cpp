#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cmath>

struct Vector2d
{
    double x{0}, y{0};
    double dist(const Vector2d &o) const
    {
        double dx = x - o.x, dy = y - o.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

class Character
{
public:
    Character(std::string n, int hp, Vector2d p) : name(std::move(n)), hp(hp), pos(p) {}
    virtual ~Character() = default;
    const Vector2d &position() const { return pos; }
    void setPos(const Vector2d &p) { pos = p; }
    bool isAlive() const { return hp > 0; }
    void damage(int d)
    {
        hp -= d;
        if (hp < 0)
            hp = 0;
    }
    const std::string &getName() const { return name; }
    int getHp() const { return hp; }

private:
    std::string name;
    int hp;
    Vector2d pos;
};

class Enemy : public Character
{
public:
    Enemy(std::string n, int hp, Vector2d p) : Character(std::move(n), hp, p) {}
    // move toward player or attack if within 1
    void update(Character &player)
    {
        double d = position().dist(player.position());
        if (d <= 1.0)
        {
            // attack
            // simple cast: reduce player HP by 1
            std::cout << "Enemy attacks player!\n";
        }
        else
        {
            // move a bit toward player
            Vector2d p = player.position();
            Vector2d me = position();
            double dx = p.x - me.x;
            double dy = p.y - me.y;
            double len = std::sqrt(dx * dx + dy * dy);
            if (len > 0)
            {
                me.x += dx / len * 0.5;
                me.y += dy / len * 0.5;
                setPos(me);
            }
        }
    }
};

// Simple Weapon and Player with switchWeapon cycle Bow->Spear->Sword
struct Weapon
{
    virtual ~Weapon() = default;
    virtual int range() const = 0;
    virtual int power() const = 0;
    virtual void attack(Character &target) const = 0;
};
struct Bow : Weapon
{
    int range() const override { return 4; }
    int power() const override { return 1; }
    void attack(Character &t) const override { t.damage(power()); }
};
struct Spear : Weapon
{
    int range() const override { return 2; }
    int power() const override { return 2; }
    void attack(Character &t) const override { t.damage(power()); }
};
struct Sword : Weapon
{
    int range() const override { return 1; }
    int power() const override { return 4; }
    void attack(Character &t) const override { t.damage(power()); }
};

class Player : public Character
{
public:
    Player(std::string n, int hp, Vector2d p) : Character(std::move(n), hp, p)
    {
        weapons.push_back(std::make_unique<Bow>());
        weapons.push_back(std::make_unique<Spear>());
        weapons.push_back(std::make_unique<Sword>());
        cur = 0;
    }
    void attack(Character &target)
    {
        if (!weapons.empty())
        {
            std::cout << "Player attacks with weapon " << cur << "\n";
            weapons[cur]->attack(target);
        }
    }
    void switchWeapon() { cur = (cur + 1) % weapons.size(); }

private:
    std::vector<std::unique_ptr<Weapon>> weapons;
    size_t cur{0};
};

int main()
{
    Player player("Hero", 20, {0, 0});
    Enemy enemy1("Goblin", 5, {5, 0});
    Enemy enemy2("Orc", 8, {6, 2});

    // simulate turns: player attacks then switches weapon
    for (int turn = 0; turn < 6; ++turn)
    {
        std::cout << "Turn " << turn << "\n";
        // player attacks nearest enemy
        double d1 = player.position().dist(enemy1.position());
        double d2 = player.position().dist(enemy2.position());
        if (enemy1.isAlive() && d1 < d2)
        {
            player.attack(enemy1);
        }
        else if (enemy2.isAlive())
        {
            player.attack(enemy2);
        }
        player.switchWeapon();
        // enemies update (move toward player — simplified)
        enemy1.update(player);
        enemy2.update(player);
        std::cout << "Enemy1 HP=" << enemy1.getHp() << " Enemy2 HP=" << enemy2.getHp() << "\n";
    }
    return 0;
}
