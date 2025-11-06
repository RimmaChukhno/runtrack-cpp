#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

// Base case for the recursion
void print()
{
    std::cout << std::endl;
}

// Variadic template for single argument
template <typename T>
void print(const T &arg)
{
    std::cout << arg << std::endl;
}

// Variadic template for multiple arguments
template <typename T, typename... Args>
void print(const T &first, const Args &...rest)
{
    std::cout << first << ", ";
    print(rest...);
}

#endif // PRINT_HPP