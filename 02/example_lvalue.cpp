#include <iostream>

struct Int {
    int value;
};

struct SumProxy {
    Int& a;
    Int& b;

    SumProxy& operator=(int target) {
        a.value = target - b.value;
        return *this;
    }
};

SumProxy operator+(Int& a, Int& b) {
    return {a, b};
}

int main() {
    Int a{2};
    Int b{3};

    a + b = 10;

    std::cout << a.value << '\n'; // 7
    std::cout << b.value << '\n'; // 3
}