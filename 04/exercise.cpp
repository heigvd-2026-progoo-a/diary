#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void print(const std::vector<int> &v) {
    for (int t : v) {
        std::cout << t << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> temperatures;

    // 1. Lire 5 températures avec push_back()
    std::cout << "Entrez 5 températures :\n";
    for (int i = 0; i < 5; i++) {
        int t;
        std::cin >> t;
        temperatures.push_back(t);
    }

    // 2. Afficher le vector
    std::cout << "\nTempératures : ";
    print(temperatures);

    // 3. Trouver min, max et moyenne
    int min = *std::min_element(temperatures.begin(), temperatures.end());
    int max = *std::max_element(temperatures.begin(), temperatures.end());
    double moyenne = std::accumulate(temperatures.begin(), temperatures.end(), 0.0) / temperatures.size();

    std::cout << "Min : " << min << "\n";
    std::cout << "Max : " << max << "\n";
    std::cout << "Moyenne : " << moyenne << "\n";

    // 4. Supprimer le dernier élément avec pop_back()
    temperatures.pop_back();

    // 5. Réafficher
    std::cout << "\nAprès suppression :\n";
    print(temperatures);

    return 0;
}
