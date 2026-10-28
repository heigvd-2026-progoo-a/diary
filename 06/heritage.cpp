#include <iostream>
#include <vector>

class Animal {
    public:
    // speak c'est une méthode virtuelle
    virtual void speak() { std::cout << "Animal is speaking\n"; }

    // Méthode virtuelle pure
    virtual void eat() = 0;
};

class Cat : public Animal {
    int lives = 9;
    public:
    void speak() { std::cout << "Meoww RonRonnnnn\n"; }
    void eat() { std::cout << "Croc\n"; }
};

class Fish : public Animal {
    public:
    void eat() { std::cout << "Blub\n"; }
};

int main() {
    std::vector<Animal*> zoo;

    zoo.push_back(new Cat());
    zoo.push_back(new Fish());

    for (auto &animal : zoo) { animal->speak(); } 
}