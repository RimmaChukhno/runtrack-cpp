#include <iostream>
#include "print.hpp"

int main()
{
    std::cout << "Testing variadic print template:\n";

    // Test with different types
    print(42);                         // single integer
    print("Hello");                    // single string
    print(1, 2, 3);                    // multiple integers
    print("Hello", 42, 3.14, "World"); // mixed types
    print(1.1, 2.2, 3.3, 4.4);         // multiple doubles

    return 0;
}