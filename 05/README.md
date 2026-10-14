# Semaine 05/16

## Constructeurs et méthodes par défaut d'une classe

Le C++ hérite du C : il doit donc accepter un code comme celui-ci :

```c
struct Class {};
int main() { Class c; }
```

Pour créer l'objet `c`, il faut un constructeur, alors que `Class` n'en déclare aucun. C'est le compilateur qui s'en charge : il génère automatiquement un **constructeur par défaut** pour toute classe qui n'en a pas. De même, à la fin du `main`, l'objet `c` sort de sa portée et doit être détruit : le compilateur génère aussi un **destructeur par défaut**.

En poussant le raisonnement plus loin, le code suivant est lui aussi parfaitement valide :

```c
Class a;     // Constructeur par défaut
Class b = a; // Constructeur par copie
a = b;       // Opérateur d'affectation
```

Ici, `b` est construit à partir d'un autre objet de type `Class` : c'est le rôle du **constructeur par copie**. Puis `a` reçoit la valeur de `b` : c'est le rôle de l'**opérateur d'affectation**, qui prend lui aussi en paramètre un objet de type `Class`. Si la classe ne les définit pas, le compilateur les génère automatiquement.

Pour observer quand chacun de ces éléments est appelé, on peut les écrire soi-même et leur faire afficher un message :

```cpp
#include <iostream>
using namespace std; // from std import *

struct Class {
    char name;

    // Constructeur
    Class(char name) : name{name} {
        cout << "Class " << name << " a été construit\n";
    }

    // Constructeur par copie
    Class(const Class &other) : name(other.name) {
        cout << "Class " << name << " construit par copie\n";
    }

    // Opérateur d'affectation
    Class operator=(const Class &other) {
        cout << "Class " << name << " a été affecté\n";
        return other;
    }

    // Destructeur
    ~Class() {
        cout << "Class " << name << " a été détruit\n";
    }
};

int main() {
    Class c('c');
    Class d('d');
    d = c;
}
```

Pour être complet, voici la liste des éléments que le compilateur peut générer automatiquement :

1. Constructeur par défaut
2. Constructeur par copie
3. Opérateur d'affectation
4. Destructeur
5. Constructeur de déplacement (C++11)
6. Opérateur d'affectation par déplacement (C++11)

Les deux derniers concernent le déplacement, que nous verrons plus tard dans le cours.

NOTE:
Si on déclare un constructeur avec un paramètre, automatiquement le constructeur par défaut
sera supprimé aussi. Souvent on s'en rend compte à la compilation parce que plus rien ne compile. 

La règle des 3: Si on a besoin de décalrer un destructeur, c'est probablement qu'on a besoin aussi de redéclarer le constructeur par copie et l'opérateur d'affectation. 

Par exemple l'exemple: [default2.cpp](default2.cpp)

## Concept RAII

Le RAII est une technique de C++ qui confie la gestion d'une ressource (un fichier, un bloc de mémoire) à un objet. Quand l'objet est créé, il obtient la ressource, et quand il disparaît, en sortant du bloc de code où il a été déclaré, son destructeur la libère automatiquement. Le programmeur n'a donc plus besoin de penser à fermer le fichier ou à rendre la mémoire : le langage s'en charge, même si une erreur interrompt le programme en cours de route. C'est un peu comme une porte qui se referme d'elle-même derrière vous, quelle que soit la manière dont vous quittez la pièce.

## Narrowing

Puisque nous parlons de constructeurs, c'est le bon moment pour introduire la notion de *narrowing* (réduction de type). Il s'agit d'une conversion de type qui peut entraîner une perte d'information, par exemple passer d'un `int` à un `char`. Depuis C++11, le langage offre un moyen de s'en protéger.

L'histoire est en réalité un peu moins glorieuse. La syntaxe du C++ comportait une ambiguïté connue sous le nom de *most vexing parse*, qui pouvait provoquer des erreurs de compilation ou des comportements inattendus. Pour la corriger, C++11 a introduit une nouvelle syntaxe d'initialisation avec des accolades `{}`, appelée *uniform initialization* ou *brace initialization*. Et tant qu'à ajouter une nouvelle syntaxe, autant qu'elle apporte quelque chose de plus : les accolades détectent les conversions avec perte d'information, ce que l'ancienne syntaxe ne permettait pas.

Aujourd'hui, on peut donc initialiser une variable de trois manières :

```cpp
// Notation héritée du C
int i = 42;
char c = i;

// Appel explicite du constructeur
int i(42);
char c(i);

// Avec accolades : le narrowing est détecté
int i{42};
char c{i};
```

À retenir : en C++, utilisez toujours l'initialisation avec accolades `{}`, qui vous protège du narrowing.

Voyons la différence sur deux classes presque identiques :

```cpp
struct A {
    char x;
    A(int x) : x(x) {}
};

struct B {
    char x;
    B(int x) : x{x} {}
};

int main() {
    A a(300); // Compile, mais x vaut 44 (300 % 256)
    B b{300}; // Erreur de compilation : narrowing détecté dans `x{x}`
}
```
