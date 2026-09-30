#pragma once

#include <iostream>

class Animal {
  public:
    void sleep();
    void eat();
};

struct Dog : public Animal {
    void bark();
};

struct Cat : public Animal {
    void meow() {
        std::cout << "Miaou\n";
    }
};
