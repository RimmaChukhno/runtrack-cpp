#include <iostream>

long long doubleArray(int* arr, size_t n) {
    long long somme = 0;
    for (size_t i = 0; i < n; ++i) {
        arr[i] *= 2;
        somme += arr[i];
    }
    return somme;
}

int main() {
    int n;
    std::cout << "Entrez le nombre d'éléments : ";
    if (!(std::cin >> n) || n <= 0) return 0;

    int *arr = new int[n];
    std::cout << "Entrez " << n << " entiers : ";
    for (int i = 0; i < n; ++i) std::cin >> arr[i];

    long long somme = doubleArray(arr, n);

    std::cout << "Tableau après doublement : ";
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << (i+1==n ? "\n" : " ");

    std::cout << "Somme après doublement : " << somme << std::endl;

    delete[] arr;
    return 0;
}
