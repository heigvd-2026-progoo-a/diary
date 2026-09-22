#include <iostream>

int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }

int main() {
    int a = add(2, 3);
    int b = add(2.5, 3.5);
    double c = add(2.5, 5); // Ambiguous
    std::cout << a << " " << b << " " << c << std::endl;
}