#include <iostream>
#include <random>
#include <vector>

class Animal {
public:
    virtual ~Animal() = default;          // Indispensable pour détruire via un Animal*

    virtual void speak() const { std::cout << "Animal is speaking\n"; }
    virtual void eat() const = 0;         // Méthode virtuelle pure : classe abstraite
};

class Cat : public Animal {
    int lives = 9;
public:
    void speak() const override { std::cout << "🐱 Meoww RonRonnnnn (" << lives << " vies)\n"; }
    void eat()   const override { std::cout << "🐱 Croc croc\n"; }
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "🐶 Wouf wouf\n"; }
    void eat()   const override { std::cout << "🐶 Slurp slurp\n"; }
};

int main() {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> coin{0, 1};

    std::vector<Animal*> zoo;

    for (int i = 0; i < 10; ++i) {
        if (coin(rng)) zoo.push_back(new Cat());
        else           zoo.push_back(new Dog());
    }

    for (Animal* animal : zoo) {
        animal->speak();   // Dispatch dynamique via la vtable
        animal->eat();
        std::cout << "---\n";
    }

    // Chaque new doit avoir son delete
    for (Animal* animal : zoo) {
        delete animal;
    }
}