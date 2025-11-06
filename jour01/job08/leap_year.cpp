#include <iostream>

int main() {
    int annee;
    std::cout << "Entrez une année (ex : 2024) : ";
    if (!(std::cin >> annee)) return 0;

    bool bissextile = (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0));

    std::cout << annee << (bissextile ? " est une année bissextile\n" : " n'est pas une année bissextile\n");
    return 0;
}
