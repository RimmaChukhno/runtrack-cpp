#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
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
    virtual void update() = 0;
    virtual void draw() const = 0;
    virtual bool isAlive() const { return true; }
};

class Manager
{
public:
    void add(std::unique_ptr<GameObject> obj) { objects.push_back(std::move(obj)); }
    void updateAll()
    {
        for (auto &o : objects)
            o->update();
        // remove dead
        objects.erase(std::remove_if(objects.begin(), objects.end(), [](const std::unique_ptr<GameObject> &o)
                                     { return !o->isAlive(); }),
                      objects.end());
    }
    void drawAll() const
    {
        for (const auto &o : objects)
            o->draw();
    }

private:
    std::vector<std::unique_ptr<GameObject>> objects;
};

struct SimpleObj : public GameObject
{
    SimpleObj(std::string n, double x, double y) : name(std::move(n))
    {
        this->x = x;
        this->y = y;
    }
    void update() override { x += 0.1; }
    void draw() const override { std::cout << name << " at (" << x << "," << y << ")\n"; }
    bool isAlive() const override { return x < 2.0; }

private:
    std::string name;
};

int main()
{
    Manager m;
    m.add(std::make_unique<SimpleObj>("A", 0.0, 0.0));
    m.add(std::make_unique<SimpleObj>("B", 0.5, 0.0));
    for (int i = 0; i < 30; i++)
    {
        std::cout << "Tick " << i << "\n";
        m.updateAll();
        m.drawAll();
    }
    return 0;
}
