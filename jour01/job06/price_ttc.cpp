#include <iostream>
#include <iomanip>

int main() {
    double priceHT, kilos, tva;
    std::cout << "Entrez le prix au kilo, le nombre de kilos et le pourcentage de TVA (séparés par des espaces) : ";
    if (!(std::cin >> priceHT >> kilos >> tva)) return 0;

    double priceTTC = priceHT * kilos * (1.0 + tva / 100.0);

    std::cout << std::fixed << std::setprecision(2)
              << "Prix TTC : " << priceTTC << std::endl;
    return 0;
}
