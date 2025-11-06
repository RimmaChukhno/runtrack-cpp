#include <iostream>
#include <vector>
#include <memory>
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
    void update() override {}
    void draw() const override { std::cout << name << " HP=" << hp << " at (" << pos.x << "," << pos.y << ")\n"; }
    void damage(int d)
    {
        hp -= d;
        if (hp < 0)
            hp = 0;
    }
    bool isAlive() const override { return hp > 0; }
    const std::string &getName() const { return name; }

private:
    std::string name;
    int hp;
};

class Projectile : public GameObject
{
public:
    Projectile(Vector2d p, Vector2d v, int dmg) : vel(v), damage(dmg) { pos = p; }
    void update() override
    {
        pos.x += vel.x;
        pos.y += vel.y;
    }
    void draw() const override { std::cout << "Projectile at (" << pos.x << "," << pos.y << ") dmg=" << damage << "\n"; }
    int getDamage() const { return damage; }

private:
    Vector2d vel;
    int damage;
};

int main()
{
    Character enemy("Orc", 6, {5, 0});
    Projectile arrow({0, 0}, {1.5, 0}, 1);
    std::vector<GameObject *> world;
    // simulate until hit
    for (int t = 0; t < 10 && enemy.isAlive(); ++t)
    {
        arrow.update();
        std::cout << "Tick " << t << ": ";
        arrow.draw();
        enemy.draw();
        if (arrow.pos.dist(enemy.pos) < 0.75)
        {
            std::cout << "Projectile hit " << enemy.getName() << " dealing " << arrow.getDamage() << "\n";
            enemy.damage(arrow.getDamage());
            break;
        }
    }
    std::cout << "Enemy HP after hit: " << (enemy.isAlive() ? "alive" : "dead") << " (" << (enemy.isAlive() ? "" : "") << ")\n";
    return 0;
}
