// Bonus : le problème du diamant.
// Animal et IPet héritent tous deux d'INamed. Sans héritage virtuel, Cat
// contiendrait deux sous-objets INamed : l'appel name() serait ambigu et
// INamed::name() resterait non implémentée du côté d'IPet, si bien que Cat
// serait abstraite. Avec « virtual » des deux côtés, un seul sous-objet INamed
// subsiste et Animal::name() en est l'unique implémentation.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ===== Interfaces : contrats purs, sans état =====
class INamed {
public:
    virtual ~INamed() = default;
    virtual const std::string& name() const = 0;
};

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

// Composition : un IPet est un ISoundEmitter enrichi
class IPet : public ISoundEmitter, public virtual INamed {
public:
    virtual std::string cuddle() const = 0;
};

// ===== Classe de base abstraite : identité et état partagé =====
class Animal : public virtual INamed {
public:
    explicit Animal(std::string name) : name_(std::move(name)) {}
    virtual ~Animal() = default;
    const std::string& name() const override { return name_; }
    virtual std::string species() const = 0;
private:
    std::string name_;
};

// ===== Classes concrètes : une identité, plusieurs capacités =====
class Cat : public Animal, public IPet, public IPredator {
public:
    using Animal::Animal;
    std::string species() const override { return "chat"; }
    std::string sound() const override { return "Miaou"; }
    std::string cuddle() const override { return "ronronne"; }
    void hunt(IPrey& prey) override {
        if (prey.isAlive()) {
            prey.beCaught();
            std::cout << name() << " attrape une proie\n";
        }
    }
};

class Mouse : public Animal, public ISoundEmitter, public IPrey {
public:
    using Animal::Animal;
    std::string species() const override { return "souris"; }
    std::string sound() const override { return alive_ ? "Couic" : "..."; }
    bool isAlive() const override { return alive_; }
    void beCaught() override { alive_ = false; }
private:
    bool alive_ = true;
};

class Owl : public Animal, public ISoundEmitter, public IPredator {
public:
    using Animal::Animal;
    std::string species() const override { return "chouette"; }
    std::string sound() const override { return "Hou hou"; }
    void hunt(IPrey& prey) override {
        if (prey.isAlive()) {
            prey.beCaught();
            std::cout << name() << " fond sur une proie\n";
        }
    }
};

// Aucun lien avec Animal : seule la capacité compte
class SmokeDetector : public ISoundEmitter {
public:
    std::string sound() const override { return "BIIIP"; }
};

// ===== Fonctions qui ne dépendent que d'une capacité =====
void concert(const std::vector<const ISoundEmitter*>& choir) {
    for (const ISoundEmitter* s : choir) std::cout << s->sound() << ' ';
    std::cout << '\n';
}

void petCorner(const IPet& pet) {
    // IPet donne désormais accès au nom, sans passer par Animal
    std::cout << pet.name() << " : " << pet.cuddle() << " (" << pet.sound() << ")\n";
}

int main() {
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Cat>("Felix"));
    zoo.push_back(std::make_unique<Mouse>("Jerry"));
    zoo.push_back(std::make_unique<Owl>("Hedwige"));
    zoo.push_back(std::make_unique<Mouse>("Speedy"));
    SmokeDetector detector;

    // Le détecteur rejoint le chœur sans être un animal
    std::vector<const ISoundEmitter*> choir{&detector};
    for (const auto& a : zoo)
        if (auto* s = dynamic_cast<const ISoundEmitter*>(a.get()))
            choir.push_back(s);

    concert(choir);

    // Chasse : chaque prédateur parcourt les proies
    for (auto& a : zoo)
        if (auto* predator = dynamic_cast<IPredator*>(a.get()))
            for (auto& b : zoo)
                if (auto* prey = dynamic_cast<IPrey*>(b.get()))
                    predator->hunt(*prey);

    concert(choir);

    // Coin câlins : seuls les IPet y ont accès
    for (const auto& a : zoo)
        if (auto* pet = dynamic_cast<const IPet*>(a.get()))
            petCorner(*pet);
}
