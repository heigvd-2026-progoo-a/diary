// Code de départ du travail dirigé : une hiérarchie purement taxonomique.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Animal {
public:
    Animal(std::string name) : name_(name) {}
    virtual ~Animal() = default;
    const std::string& name() const { return name_; }
    virtual std::string species() const = 0;
private:
    std::string name_;
};

class Cat : public Animal {
public:
    using Animal::Animal;
    std::string species() const override { return "chat"; }
};

class Mouse : public Animal {
public:
    using Animal::Animal;
    std::string species() const override { return "souris"; }
};

int main() {
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Cat>("Felix"));
    zoo.push_back(std::make_unique<Mouse>("Jerry"));
    zoo.push_back(std::make_unique<Mouse>("Speedy"));

    for (const auto& a : zoo)
        std::cout << a->name() << " est un(e) " << a->species() << '\n';
}
