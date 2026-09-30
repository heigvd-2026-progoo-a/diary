# Semaine 03/16

- [ ] Classe et objet
- [ ] Visibilité (public, protégé, privé)
- [ ] Héritage

## Visibilité

- Public
- Protégé
- Privé

```cpp
// Classe avec membres publics par défaut
struct Class {
    int attribute;
    int method() { return attribute * 2; }
};

// Classe avec membres privés par défaut
class Class {
    int attribute;
    int method() { return attribute * 2; }
};

// Les mots clés public, protected et private
class Class {
    public:
        int attribute;
        int method() { return attribute * 2; }
}
struct Class {
    private:
        int attribute;
        int method() { return attribute * 2; }
}

class Human {
    public:
        void eat() {}
        void sleep() {}
    protected:
        void think() {}
    private:
        void die() {}
};
```

## Héritage

```cpp
class Human {
    public:
        void eat() {}
        void sleep() {}
    protected:
        void think() {}
    private:
        void die() {}
};

class Student : public Human {
    public:
        void study() {
            while(notReady()) {
                eat();
                read();
                think(); // Accessible car Student hérite de Human
                sleep();
            }
            die(); // Erreur : die() est privé à Human
        }
    private:
        bool notReady() { return true; }
        void read() {}
};

int main() {
    Human human;
    human.eat();
    human.think(); // Erreur : think() est protégé
```

```python
class Human:
    def eat(self):
        pass

    def sleep(self):
        pass

class Student(Human):
    def study(self):
        pass
```


## Class versus Object

```cpp
class Ball() {}; // Définition d'une classe Ball

Ball ball; // Création d'un objet de type Ball (instance)
int i = 42; // Créer un objet de type int (instance)
```

## Exercice

Déclarez une dans un nouveau fichier C++ une class `Animal` avec les attributs `age` et `weight` et les méthodes `eat()` et `sleep()`. Créez ensuite une classe `Dog` qui hérite de la classe `Animal` et ajoutez une méthode `bark()`. Enfin, créez un objet de type `Dog` et appelez ses méthodes.

Faite pareil avec la classe `Cat` qui hérite de la classe `Animal` et ajoutez une méthode `meow()`. Créez un objet de type `Cat` et appelez ses méthodes.

`bark` fait `"Woof!" et `meow` fait "Meow!". `sleep` fait `"Zzz..."` et `eat` fait `"Miam..."`.