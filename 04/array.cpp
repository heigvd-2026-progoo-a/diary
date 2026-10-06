#include <array>
#include <iostream>

int main() {
    auto i = 42;

    std::array<int, 3> a;
    int b[10];

    a.fill(42);

    // Variante traditionnelle (à éviter)
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << std::endl;
    }
    std::cout << "-------\n";

    // Variante avec itérateur
    for (auto v = a.begin(); v != a.end(); v++) {
        std::cout << *v << std::endl;
    }

    // Sucre syntaxique
    for (auto v : a) {
        std::cout << v << std::endl;
    }
}