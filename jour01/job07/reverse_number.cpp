#include <iostream>
#include <cstdlib>

int main() {
    long long n;
    std::cout << "Entrez un nombre entier : ";
    if (!(std::cin >> n)) return 0;

    bool negatif = (n < 0);
    n = std::llabs(n);

    long long inverse = 0;
    while (n > 0) {
        inverse = inverse * 10 + (n % 10);
        n /= 10;
    }
    if (negatif) inverse = -inverse;

    std::cout << "Nombre inversé : " << inverse << std::endl;
    return 0;
}
