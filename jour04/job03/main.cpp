#include <iostream>
#include "box_pointer.hpp"

int main()
{
    std::cout << "Testing Box pointer specialization:\n";

    // Create an integer on heap
    int *number = new int(42);

    // Create box with pointer
    Box<int *> pointerBox(number);

    // Access dereferenced content
    std::cout << "Box contains: " << pointerBox.get() << std::endl;

    // Modify through dereferenced access
    pointerBox.get() = 100;
    std::cout << "Modified value: " << pointerBox.get() << std::endl;

    // Clean up
    delete number;

    return 0;
}