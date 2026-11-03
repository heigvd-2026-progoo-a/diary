// Étape 1 : déclarer trois interfaces.
// Le reste du programme est inchangé : les interfaces existent, mais personne
// ne les implémente encore.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ===== Interfaces : contrats purs, sans état =====
class ISoundEmitter {
public:
    virtual ~ISoundEmitter() = default;
    virtual std::string sound() const = 0;
};

class IPrey {
public:
    virtual ~IPrey() = default;
    virtual bool isAlive() const = 0;
    virtual void beCaught() = 0;
};

class IPredator {
public:
    virtual ~IPredator() = default;
    virtual void hunt(IPrey& prey) = 0;
};

// ===== Code de départ =====
class Animal {
public:
    explicit Animal(std::string name) : name_(std::move(name)) {}
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
    // Vérification demandée : décommenter la ligne suivante produit
    //   error: cannot declare variable 'e' to be of abstract type 'ISoundEmitter'
    // ISoundEmitter e;

    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Cat>("Felix"));
    zoo.push_back(std::make_unique<Mouse>("Jerry"));
    zoo.push_back(std::make_unique<Mouse>("Speedy"));

    for (const auto& a : zoo)
        std::cout << a->name() << " est un(e) " << a->species() << '\n';
}
