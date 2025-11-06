#include <iostream>
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

struct GameObject
{
    Vector2d pos;
    virtual void update() = 0;
    virtual void draw() const = 0;
    virtual bool blocks() const { return true; }
};

struct Moving : public GameObject
{
    Vector2d vel;
    Moving(double x, double y, double vx, double vy)
    {
        pos.x = x;
        pos.y = y;
        vel.x = vx;
        vel.y = vy;
    }
    void update() override
    {
        pos.x += vel.x;
        pos.y += vel.y;
    }
    void draw() const override { std::cout << "Obj at (" << pos.x << "," << pos.y << ")\n"; }
};

// Simple collision prevention: if next pos would overlap another blocking object, cancel movement
void resolveCollisions(Moving &m, const GameObject &other)
{
    Vector2d next{m.pos.x + m.vel.x, m.pos.y + m.vel.y};
    if (other.blocks())
    {
        double d = std::sqrt((next.x - other.pos.x) * (next.x - other.pos.x) + (next.y - other.pos.y) * (next.y - other.pos.y));
        if (d < 1.0)
        { // collision: cancel movement
            m.vel.x = 0;
            m.vel.y = 0;
        }
    }
}

int main()
{
    Moving a(0, 0, 0.7, 0);
    Moving b(1.2, 0, 0, 0);
    std::cout << "Before: \n";
    a.draw();
    b.draw();
    resolveCollisions(a, b);
    a.update();
    b.update();
    std::cout << "After: \n";
    a.draw();
    b.draw();
    return 0;
}
