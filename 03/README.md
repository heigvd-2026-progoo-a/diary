
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
