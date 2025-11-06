#include <iostream>
#include <cstdint>

int main() {
    uint32_t x;
    std::cout << "Entrez un entier non signé (32 bits) : ";
    if (!(std::cin >> x)) return 0;

    int parite = 0;
    while (x) {
        parite ^= (x & 1);
        x >>= 1;
    }

    std::cout << (parite == 0 ? "Nombre pair de bits à 1\n" : "Nombre impair de bits à 1\n");
    return 0;
}
