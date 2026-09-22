# Semaine 02/16

- [ ] Espaces de noms (namespace)
- [ ] Surcharge paramétrique (overloading)
- [ ] Left/Right value (lvalue/rvalue)
- [ ] Références (references)

## Mangling 

Consiste à transformer le nom d'une fonction en un nom unique pour le linker en ajoutant un préfixe à la fonction. 

On le fait massivement en C car il n'y a pas d'espaces de noms.

```c
int int_add(int, int);
```

En C++ on peut utiliser un espace de nom.

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

Lorsque plusieurs fonctions portent le même nom mais ont des signatures différentes, le compilateur choisit celle qui correspond aux arguments passés.

```cpp
#include <iostream>

int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }

int main() {
    int a = add(2, 3);
    int b = add(2.5, 3.5);
    double c = add(2.5, 5); // Ambiguous
    std::cout << a << " " << b << " " << c << std::endl;
}
```

## Paramètres optionnels

```cpp
#include <iostream>

void greet(std::string name = "World") {
    std::cout << "Hello, " << name << "!" << std::endl;
}

int main() {
    greet(); // Affiche "Hello, World!"
    greet("Alice"); // Affiche "Hello, Alice!"
    return 0;
}
```

## Référence

Une référence c'est un alias pour une variable existante. Elle doit être initialisée lors de sa déclaration et ne peut pas être réassignée à une autre variable.

Derrière le rideau, c'est un pointeur constant mais il doit impérativement être initialisé à une variable existante.

```cpp
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

## Left/Right value (lvalue/rvalue)

Une lvalue (left value) est une expression qui fait référence à un emplacement mémoire identifiable. Une rvalue (right value) est une expression qui ne fait pas référence à un emplacement mémoire identifiable, souvent une variable temporaire ou une valeur littérale.
