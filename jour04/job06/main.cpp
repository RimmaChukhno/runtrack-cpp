#include <iostream>
#include "shape_factory_template.hpp"

int main()
{
    std::cout << "Testing Template ShapeFactory:\n";

    // Create a circle using template factory
    auto circle = ShapeFactory<Circle>::createShape();
    std::cout << "Created circle: ";
    circle->draw();

    // Create a rectangle using template factory
    auto rectangle = ShapeFactory<Rectangle>::createShape();
    std::cout << "Created rectangle: ";
    rectangle->draw();

    return 0;
}