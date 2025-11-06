#include <iostream>
#include <string>

// Minimal Character used by weapons
class Character
{
public:
    Character(std::string n, int hp) : name(std::move(n)), hp(hp) {}
    void damage(int d)
    {
        hp -= d;
        if (hp < 0)
            hp = 0;
    }
    bool isAlive() const { return hp > 0; }
    const std::string &getName() const { return name; }
    int getHp() const { return hp; }

private:
    std::string name;
    int hp;
};

struct Weapon
{
    virtual ~Weapon() = default;
    virtual int range() const = 0;
    virtual int power() const = 0;
    virtual void attack(Character &target) const = 0;
};

struct Bow : public Weapon
{
    int range() const override { return 4; }
    int power() const override { return 1; }
    void attack(Character &target) const override { target.damage(power()); }
};

struct Spear : public Weapon
{
    int range() const override { return 2; }
    int power() const override { return 2; }
    void attack(Character &target) const override { target.damage(power()); }
};

struct Sword : public Weapon
{
    int range() const override { return 1; }
    int power() const override { return 4; }
    void attack(Character &target) const override { target.damage(power()); }
};

int main()
{
    Character enemy("Orc", 6);
    Bow bow;
    Spear spear;
    Sword sword;

    std::cout << enemy.getName() << " HP=" << enemy.getHp() << "\n";
    bow.attack(enemy);
    std::cout << "After bow: HP=" << enemy.getHp() << "\n";
    spear.attack(enemy);
    std::cout << "After spear: HP=" << enemy.getHp() << "\n";
    sword.attack(enemy);
    std::cout << "After sword: HP=" << enemy.getHp() << "\n";
    return 0;
}
