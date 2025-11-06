#include <iostream>
#include <algorithm>

int main() {
    int a, b;
    std::cout << "Entrez deux nombres entiers (a b): ";
    if (!(std::cin >> a >> b)) return 0;
    std::cout << "avant: a=" << a << " b=" << b << std::endl;
    std::swap(a, b);
    std::cout << "apres: a=" << a << " b=" << b << std::endl;
    return 0;
}
