#include <iostream>
#include <random>
#include <array>

enum Specialite { IA, Web, Logiciel, SystemeImmersif, Cybersecurite, COUNT };

int main() {
    std::array<const char*, COUNT> noms = {
        "IA", "Web", "Logiciel", "Système immersif", "Cybersécurité"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(12, 66);

    std::cout << "Nombre d'étudiants par spécialité :\n";
    for (int i = 0; i < COUNT; ++i) {
        int nb = dist(gen);
        std::cout << noms[i] << " : " << nb << " étudiants\n";
    }
    return 0;
}
