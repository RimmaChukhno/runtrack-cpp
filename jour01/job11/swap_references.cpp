#include <iostream>

void swapValues(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int main() {
    int a, b;
    std::cout << "Entrez deux entiers (a b) : ";
    if (!(std::cin >> a >> b)) return 0;

    std::cout << "Avant échange : a=" << a << " b=" << b << std::endl;
    swapValues(a, b);
    std::cout << "Après échange : a=" << a << " b=" << b << std::endl;

    return 0;
}
