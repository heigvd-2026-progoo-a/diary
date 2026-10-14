# Semaine 05/16


```cpp
struct Class {
    // Constructeur par défaut
    Class() {
        std::cout << "Class a été construit\n";
    }

    // Constructeur par copie
    Class(const Class &other) { }

    // Opérateur d'affectation
    Class operator=(const Class &other) {}

    // Destructeur par défaut
    ~Class() {}
};

{
    Class c; // Constructeur par défaut
    Class d = c;
    c = d;
}
```


## Narrowing

// Notation standard C
int i = 42;
char c = i;

// Appel C++ explicite du constructeur
int i(42);
char c(i);

// Avec narrowing (protection de réduction de type)
int i{42};
char c{i};

En C++ utlilisez toujours l'appel avec test de narrowing `{}` 