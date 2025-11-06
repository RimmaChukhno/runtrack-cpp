#include <iostream>
#include "shape.hpp"

int main()
{
    std::cout << "Testing Shape hierarchy and drawShape template:\n";

    Circle circle;
    Rectangle rectangle;

    std::cout << "Using drawShape with Circle:" << std::endl;
    drawShape(circle);

    std::cout << "\nUsing drawShape with Rectangle:" << std::endl;
    drawShape(rectangle);

    return 0;
}