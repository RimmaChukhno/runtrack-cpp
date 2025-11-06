#include <iostream>
#include <limits>

int main() {
    int n;
    std::cout << "Entrez le nombre d'éléments : ";
    if (!(std::cin >> n) || n <= 0) return 0;

    int *tab = new int[n];
    std::cout << "Entrez " << n << " entiers : ";
    for (int i = 0; i < n; ++i) std::cin >> tab[i];

    int minVal = std::numeric_limits<int>::max();
    for (int *p = tab; p < tab + n; ++p) {
        if (*p < minVal) minVal = *p;
    }

    std::cout << "Valeur minimale : " << minVal << std::endl;
    delete[] tab;
    return 0;
}
