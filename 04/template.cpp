#include <iostream>

template<class T> 
T add(T a, T b) {
    T c = a + b;
    return c;
}

template<class T, int U, float V> 
T foo(T a) {
    return (a + U) * V;
}

int main() {
    float u = 23;
    int v(42);
    std::cout << add(u, static_cast<float>(v));

    std::cout << add<float>(u, v);

    std::cout << foo<int, 5, 3.14f>(42);
}