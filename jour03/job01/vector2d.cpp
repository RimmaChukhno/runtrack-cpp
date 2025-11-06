#include <iostream>
#include <cmath>

class Vector2d
{
private:
    double x_ = 0;
    double y_ = 0;

public:
    Vector2d() = default;
    Vector2d(double x, double y) : x_(x), y_(y) {}
    double x() const { return x_; }
    double y() const { return y_; }
    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }

    Vector2d operator+(const Vector2d &o) const { return Vector2d(x_ + o.x_, y_ + o.y_); }
    Vector2d operator-(const Vector2d &o) const { return Vector2d(x_ - o.x_, y_ - o.y_); }

    double distance(const Vector2d &other) const
    {
        double dx = x_ - other.x_;
        double dy = y_ - other.y_;
        return std::sqrt(dx * dx + dy * dy);
    }
};

int main()
{
    Vector2d a(1.0, 2.0);
    Vector2d b(4.0, 6.0);
    Vector2d c = a + b;
    Vector2d d = b - a;

    std::cout << "a = (" << a.x() << ", " << a.y() << ")\n";
    std::cout << "b = (" << b.x() << ", " << b.y() << ")\n";
    std::cout << "a + b = (" << c.x() << ", " << c.y() << ")\n";
    std::cout << "b - a = (" << d.x() << ", " << d.y() << ")\n";
    std::cout << "distance(a,b) = " << a.distance(b) << "\n";
    return 0;
}
