#include <iostream>
#include "box.hpp"

int main()
{
    std::cout << "Testing Box class:\n";

    // Test with integer
    Box<int> intBox(42);
    std::cout << "Integer box contains: " << intBox.get() << std::endl;

    // Test with string
    Box<std::string> stringBox("Hello, Box!");
    std::cout << "String box contains: " << stringBox.get() << std::endl;

    // Test modifying content
    intBox.set(100);
    std::cout << "Modified integer box contains: " << intBox.get() << std::endl;

    return 0;
}