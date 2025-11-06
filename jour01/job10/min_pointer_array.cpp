#include <iostream>
#include <limits>

int main() {
    int n;
    std::cout << "Entrez le nombre d'éléments : ";
    if (!(std::cin >> n) || n <= 0) return 0;

    int *valeurs = new int[n];
    int **ptrs = new int*[n];

    std::cout << "Entrez " << n << " entiers : ";
    for (int i = 0; i < n; ++i) {
        std::cin >> valeurs[i];
        ptrs[i] = &valeurs[i];
    }

    int minVal = std::numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
        if (*(ptrs[i]) < minVal) minVal = *(ptrs[i]);
    }

    std::cout << "Minimum trouvé via pointeurs : " << minVal << std::endl;
    delete[] valeurs;
    delete[] ptrs;
    return 0;
}
