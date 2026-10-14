# Semaine 03/16

- [ ] Classes et objets
- [ ] Visibilité (publique, protégée, privée)
- [ ] Héritage

## Visibilité

Les membres d'une classe peuvent avoir trois niveaux de visibilité :

- public (`public`) ;
- protégé (`protected`) ;
- privé (`private`).

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

// Les mots-clés public, protected et private
class Class {
    public:
        int attribute;
        int method() { return attribute * 2; }
};
struct Class {
    private:
        int attribute;
        int method() { return attribute * 2; }
};

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

La classe `Student` hérite de `Human` : elle accède à ses membres publics et protégés, mais pas à ses membres privés.

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
}
```

Le même héritage en Python :

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


## Classe et objet

```cpp
class Ball {}; // Définition d'une classe Ball

Ball ball; // Création d'un objet de type Ball (instance)
int i = 42; // Créer un objet de type int (instance)
```

## Exercice

Dans un nouveau fichier C++, déclarez une classe `Animal` dotée des attributs `age` et `weight` et des méthodes `eat()` et `sleep()`. Créez ensuite une classe `Dog` qui hérite d'`Animal` et ajoutez-lui une méthode `bark()`. Enfin, créez un objet de type `Dog` et appelez ses méthodes.

Faites de même avec une classe `Cat`, qui hérite elle aussi d'`Animal` et possède une méthode `meow()`. Créez un objet de type `Cat` et appelez ses méthodes.

Chaque méthode affiche un message : `bark()` affiche `"Woof!"`, `meow()` affiche `"Meow!"`, `sleep()` affiche `"Zzz..."` et `eat()` affiche `"Miam..."`.
