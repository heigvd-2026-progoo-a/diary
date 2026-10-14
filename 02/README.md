# Semaine 02/16

- [x] Espaces de noms (*namespaces*)
- [x] Surcharge paramétrique (*overloading*)
- [x] Valeurs à gauche et à droite (*lvalue* / *rvalue*)
- [x] Références (*references*)

## Décoration de noms (*mangling*)

Le *mangling* consiste à transformer le nom d'une fonction en un nom unique pour l'éditeur de liens (*linker*), en lui ajoutant un préfixe.

En C, faute d'espaces de noms, on recourt massivement à cette technique en préfixant soi-même le nom des fonctions :

```c
int int_add(int, int);
```

En C++, on peut utiliser un espace de noms à la place :

```cpp
namespace math {
    namespace integers {
        int add(int a, int b) {
            return a + b;
        }
    }
    namespace reals {
        double add(double a, double b) {
            return a + b;
        }
    }
}

int main() {
    int result = math::integers::add(2, 3);
    double result2 = math::reals::add(2.5, 3.5);
    return 0;
}
```

## Surcharge paramétrique (overloading)

Lorsque plusieurs fonctions portent le même nom mais ont des signatures différentes, le compilateur choisit celle qui correspond aux arguments transmis lors de l'appel.

```cpp
#include <iostream>

int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }

int main() {
    int a = add(2, 3);
    double b = add(2.5, 3.5);
    double c = add(2.5, 5); // Ambigu
    std::cout << a << " " << b << " " << c << std::endl;
}
```

## Paramètres optionnels

Un paramètre peut recevoir une valeur par défaut, utilisée lorsque l'argument est omis à l'appel :

```cpp
#include <iostream>
#include <string>

void greet(std::string name = "World") {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {
    greet(); // Affiche "Hello, World!"
    greet("Alice"); // Affiche "Hello, Alice!"
    return 0;
}
```

## Références

Une référence est un alias d'une variable existante. Elle doit être initialisée dès sa déclaration et ne peut plus, ensuite, désigner une autre variable.

En coulisses, une référence se comporte comme un pointeur constant, à ceci près qu'elle doit impérativement être initialisée avec une variable existante.

```cpp
#include <iostream>

void display(int i) {
    std::cout << "Value: " << i << std::endl;
}

int main() {
    int i = 10;
    int &ref = i; // ref est une référence à i;
    int *ptr = &i;

    display(i);
    display(ref); // ref est automatiquement déréférencée
    display(*ptr); // ptr est déréférencé
}
```

## Valeurs à gauche et à droite (*lvalue* / *rvalue*)

Une *lvalue* (*left value*) est une expression qui désigne un emplacement mémoire identifiable. Une *rvalue* (*right value*) est une expression qui ne désigne aucun emplacement mémoire identifiable : il s'agit le plus souvent d'une valeur temporaire ou d'une valeur littérale.
