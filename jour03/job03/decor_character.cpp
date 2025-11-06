#include <iostream>
#include <string>

class Vector2d
{
public:
    double x{0}, y{0};
};

class GameObject : public Vector2d
{
public:
    virtual ~GameObject() = default;
    virtual void draw() const = 0;
    virtual void update() = 0;
};

class Decor : public GameObject
{
public:
    Decor(double x, double y, const std::string &desc) : desc_(desc)
    {
        this->x = x;
        this->y = y;
    }
    void draw() const override { std::cout << "Decor: " << desc_ << " at (" << x << "," << y << ")\n"; }
    void update() override { /* does not move */ }

private:
    std::string desc_;
};

class Character : public GameObject
{
public:
    Character(const std::string &name, int hp, double x = 0, double y = 0) : name_(name), hp_(hp)
    {
        this->x = x;
        this->y = y;
    }
    void draw() const override { std::cout << "Character " << name_ << " HP=" << hp_ << " at (" << x << "," << y << ")\n"; }
    void update() override { /* could move, here static */ }
    bool isAlive() const { return hp_ > 0; }
    void damage(int d)
    {
        hp_ -= d;
        if (hp_ < 0)
            hp_ = 0;
    }

private:
    std::string name_;
    int hp_;
};

int main()
{
    Decor tree(5, 2, "Tree");
    Character hero("Alice", 10, 1, 1);
    tree.draw();
    hero.draw();
    hero.damage(3);
    std::cout << "After damage: ";
    hero.draw();
    std::cout << "Is alive? " << (hero.isAlive() ? "yes" : "no") << "\n";
    return 0;
}
