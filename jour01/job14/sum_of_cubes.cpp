#include <iostream>

int main() {
    int N;
    std::cout << "Entrez N : ";
    if (!(std::cin >> N)) return 0;

    if (N < 5) {
        std::cout << "N < 5, somme = 0\n";
        return 0;
    }

    long long somme = 0;
    for (int i = 5; i <= N; ++i) somme += 1LL * i * i * i;

    std::cout << "Somme des cubes de 5^3 à " << N << "^3 = " << somme << std::endl;
    return 0;
}
