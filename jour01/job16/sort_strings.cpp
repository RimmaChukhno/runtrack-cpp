#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

int main() {
    int n;
    std::cout << "Entrez le nombre de chaînes : ";
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<std::string> mots(n);
    std::cout << "Entrez " << n << " mots (un par ligne) :\n";
    for (int i = 0; i < n; ++i) std::cin >> mots[i];

    std::vector<const char*> ptrs(n);
    for (int i = 0; i < n; ++i) ptrs[i] = mots[i].c_str();

    std::sort(ptrs.begin(), ptrs.end(), [](const char* a, const char* b) {
        return std::strcmp(a, b) < 0;
    });

    std::cout << "Chaînes triées :\n";
    for (const char* s : ptrs) std::cout << s << std::endl;
    return 0;
}
