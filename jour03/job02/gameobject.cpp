#include <iostream>
#include <cmath>

class Vector2d
{
public:
    double x{0}, y{0};
    Vector2d() = default;
    Vector2d(double xx, double yy) : x(xx), y(yy) {}
};

class GameObject : public Vector2d
{
public:
    GameObject() = default;
    GameObject(double x, double y) : Vector2d(x, y) {}
    virtual ~GameObject() = default;
    virtual void draw() const = 0;
    virtual void update() = 0;
};

class Dummy : public GameObject
{
public:
    Dummy(double x, double y, const std::string &name) : GameObject(x, y), name_(name) {}
    void draw() const override { std::cout << "Dummy(" << name_ << ") at (" << x << "," << y << ")\n"; }
    void update() override
    {
        x += 1.0;
        y += 0.5;
    }

private:
    std::string name_;
};

int main()
{
    Dummy d(0, 0, "A");
    for (int i = 0; i < 3; i++)
    {
        d.draw();
        d.update();
    }
    std::cout << "After updates: ";
    d.draw();
    return 0;
}
