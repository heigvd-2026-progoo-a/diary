#include <iostream>

int global = 1;

int &select(bool b) {
    int local = 42;
    return b ? local : global;
}

int main() {
    std::cout << select(false) << std::endl; // 1
    std::cout << select(true) << std::endl; // 42

    select(false) = 23;
    std::cout << select(false) << std::endl; // 23

    select(true) = 88;
    std::cout << select(true) << std::endl; // 42
}