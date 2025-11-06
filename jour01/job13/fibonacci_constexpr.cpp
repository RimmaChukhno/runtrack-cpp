#include <iostream>

constexpr unsigned long long fib(unsigned n) {
    return (n < 2) ? n : fib(n - 1) + fib(n - 2);
}

int main() {
    std::cout << "Les 10 premiers nombres de Fibonacci : ";
    for (unsigned i = 0; i < 10; ++i)
        std::cout << fib(i) << (i+1==10 ? "\n" : " ");
    return 0;
}
