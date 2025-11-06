#include <iostream>
#include "max.hpp"

int main()
{
    std::cout << "Testing max function:\n";

    // Test with integers
    std::cout << "max(5, 3) = " << max(5, 3) << std::endl;

    // Test with doubles
    std::cout << "max(3.14, 2.718) = " << max(3.14, 2.718) << std::endl;

    // Test with chars
    std::cout << "max('a', 'z') = " << max('a', 'z') << std::endl;

    return 0;
}