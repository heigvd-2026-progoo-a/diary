#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

int accumulate(std::vector<int> v, int init, std::function<int(int, int)> f) {
    int acc = init;
    for (auto &el : v) {
        acc = f(acc, el);
    }
    return acc;
}


int main() {
    std::vector<int> v{4, 8, 15, 16, 23, 42};

    // sum : lambda sans capture, utilisée comme opération binaire
    int sum = std::accumulate(v.begin(), v.end(), 0,
        [](int acc, int x) { return acc + x; });
    std::cout << "sum = " << sum << '\n';   // 108

    // sum sans accumulate
    {
        int sum = 0;
        std::for_each(v.begin(), v.end(),
            [&sum](int& x) { 
                sum += x;
                return x;
            });
        std::cout << "sum = " << sum; 
    }

    // alter : closure capturant un facteur, modifie le vecteur en place
    int facteur = 10;
    std::for_each(v.begin(), v.end(),
        [facteur](int& x) { x *= facteur; });

    for (int x : v) std::cout << x << ' ';   // 40 80 150 160 230 420
    std::cout << '\n';
}