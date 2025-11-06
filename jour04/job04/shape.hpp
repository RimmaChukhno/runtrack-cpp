#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

class Rectangle : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing a Rectangle" << std::endl;
    }
};

template <typename T>
void drawShape(const T &shape)
{
    static_assert(std::is_base_of<Shape, T>::value, "T must be derived from Shape");
    shape.draw();
}

#endif // SHAPE_HPP