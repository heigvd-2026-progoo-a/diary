# Semaine 04/16

- [x] Templates (de base)
- [x] Conteneurs séquentiels de la STL
- [ ] Surcharge d'opérateurs

Exemples de la semaine :

| Sujet | Fichier |
|-------|---------|
| Templates de fonctions et paramètres non-types | [template.cpp](template.cpp) |
| `std::array` et les trois façons de parcourir un conteneur | [array.cpp](array.cpp) |
| Réimplémentation d'un `std::array` avec un template de classe | [Array.cpp](Array.cpp) |
| `std::deque` / `std::vector` | [vector.cpp](vector.cpp) |
| Surcharge d'opérateurs sur une classe `Point` | [operator.cpp](operator.cpp) |
| Solution de l'exercice sur les températures (`std::vector`) | [exercise.cpp](exercise.cpp) |

## Templates

Un *template* est un « moule » que le compilateur utilise pour générer du code pour un type donné. Sans template, il faut écrire une surcharge par type (`int`, `long long`, `float`, `double`…) alors que le corps est identique. Avec un template, on écrit la fonction une seule fois et le compilateur l'**instancie** pour chaque type effectivement utilisé.

```cpp
template<class T>
T add(T a, T b) {
    return a + b;
}


int add(int a, int b) {
    return a + b;
}

long long add(long long a, long long b) {
    return a + b;
}

float add(float a, float b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}
```

Le template du haut remplace les quatre surcharges du bas. Le type `T` doit simplement supporter l'opérateur `+` : c'est vérifié à la compilation, au moment de l'instanciation.

Voir [template.cpp](template.cpp) :

- **Déduction du type** : `add(u, v)` avec deux `float` déduit `T = float`. Si les arguments ont des types différents (`float` et `int`), la déduction échoue. On peut alors convertir explicitement (`static_cast<float>(v)`) ou imposer le type : `add<float>(u, v)`.
- **Paramètres non-types** : un template peut aussi prendre des valeurs connues à la compilation, comme `template<class T, int U, float V>`. Ici `foo<int, 5, 3.14f>(42)` fixe `U` et `V` à la compilation. Attention : un paramètre template de type `float` n'est accepté que depuis C++20.

### Template de classe

[Array.cpp](Array.cpp) réimplémente un `std::array` minimaliste avec `template<class T, std::size_t N>`. La taille `N` fait partie du type : `Array<int, 3>` et `Array<int, 4>` sont deux types différents, et il n'y a aucune allocation dynamique (les éléments sont stockés directement dans l'objet). On y retrouve :

- les alias de types habituels de la STL (`value_type`, `reference`, `iterator`…) ;
- l'accès aux éléments : `operator[]` (sans vérification), `at()` (qui lève `std::out_of_range`), `front()`, `back()`, `data()` ;
- les itérateurs `begin()` / `end()`, qui sont de simples pointeurs ;
- les versions `const` et non-`const` de chaque accesseur, pour pouvoir utiliser le conteneur dans les deux contextes.

## Conteneurs séquentiels de la STL

Un conteneur séquentiel stocke ses éléments dans un ordre défini par l'utilisateur. Ceux vus cette semaine :

- `std::array<T, N>` : taille fixe connue à la compilation, aucune allocation dynamique ;
- `std::vector<T>` : tableau dynamique contigu, accès aléatoire en O(1), ajout en fin amorti en O(1) ;
- `std::deque<T>` : file à double extrémité, ajout/suppression efficace au début *et* à la fin.

### Parcourir un conteneur

[array.cpp](array.cpp) montre trois façons de parcourir un conteneur, de la plus ancienne à la plus idiomatique :

1. **Boucle avec indice** : `for (int i = 0; i < a.size(); i++)`. À éviter : mélange `int` signé et `size_t` non signé, et ne fonctionne pas avec tous les conteneurs.
2. **Itérateurs** : `for (auto v = a.begin(); v != a.end(); v++)`, avec `*v` pour accéder à l'élément. Fonctionne avec tous les conteneurs.
3. **Range-based for** : `for (auto v : a)`. C'est du sucre syntaxique qui se traduit par la version avec itérateurs. Utiliser `auto&` ou `const auto&` pour éviter les copies.

### `std::deque`

[vector.cpp](vector.cpp) utilise un `std::deque<int>` avec `push_back()`, `pop_back()` et `size()`. L'API est quasiment identique à celle de `std::vector`, à une différence près : `std::deque` n'a pas de `capacity()` (ligne commentée dans l'exemple), car ses éléments ne sont pas stockés dans un bloc de mémoire contigu.

## Surcharge d'opérateurs

C++ permet de redéfinir le comportement des opérateurs (`+`, `-`, `*`, `<<`…) pour nos propres types. Un opérateur est simplement une fonction avec un nom spécial (`operator+`), qui peut être :

- une **fonction membre** : l'opérande de gauche est l'objet courant (`this`) ;
- une **fonction libre** : nécessaire quand l'opérande de gauche n'est pas de notre type (`42 + a`, ou `std::cout << p`).

Voir [operator.cpp](operator.cpp) : la classe `Point` définit `operator+` (addition de deux points) et `operator*` (multiplication par un scalaire), ce qui permet d'écrire `(p + q) * 42` plutôt que `p.add(q)`. Les deux écritures sont équivalentes, mais la première est plus lisible.

### Afficher un objet avec `<<`

```cpp
class Prout {
    public:
    std::string to_string() { return "42"; }
};

std::ostream operator<<(std::ostream &os, Prout&prout) {
    return os << prout.to_string();
}

int main() {
    Prout p;
    std::cout << p;
}
```

L'opérateur `<<` doit être une fonction libre, puisque l'opérande de gauche est un `std::ostream`. Il doit retourner le flux **par référence** (`std::ostream &`) : un flux n'est pas copiable, et c'est ce qui permet d'enchaîner `std::cout << p << "\n"`. Dans l'exemple ci-dessus le type de retour est `std::ostream` (par valeur), ce qui ne compile pas.

### Opérateurs symétriques

```cpp
struct MyInt {
    int value;
    MyInt operator+(MyInt &other) { return MyInt(value + other.value); }

    MyInt operator+(int &other) { return MyInt(value + other); }

    MyInt operator-(MyInt &other) { return MyInt(value - other.value); }
};

MyInt operator+(int u, MyInt &v) {
}

int main() {
    MyInt a, b;
    MyInt c = a + 42;
    MyInt d = 42 + a;
}
```

`a + 42` est résolu par la fonction membre `MyInt::operator+(int)`, mais `42 + a` ne peut pas l'être : l'opérande de gauche est un `int`, on ne peut donc pas lui ajouter de méthode. Il faut une fonction libre `operator+(int, MyInt)`, qui doit bien sûr retourner une valeur (le corps est vide dans l'exemple).

Pour pouvoir écrire `a + 42` avec un littéral, les paramètres doivent être des références constantes (`const MyInt &`, `const int &`) ou des valeurs : une référence non-`const` (`int &`) ne peut pas se lier à un temporaire comme `42`. Par ailleurs, il faut marquer les opérateurs `const` quand ils ne modifient pas l'objet.

Voici un petit exercice faisable en **12 minutes** avec `std::vector`.

### Exercice — Gestion rapide de températures

Écris un programme C++ qui :

1. Demande à l’utilisateur de saisir **5 températures** entières.
2. Les stocke dans un `std::vector<int>`.
3. Affiche toutes les températures.
4. Affiche :
   - la température minimale,
   - la température maximale,
   - la moyenne.
5. Supprime la dernière température avec `pop_back()` puis réaffiche le `vector`.

Exemple attendu :

```text
Entrez 5 températures :
12 8 15 20 10

Températures : 12 8 15 20 10
Min : 8
Max : 20
Moyenne : 13

Après suppression :
12 8 15 20
```

Squelette de départ :

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> temperatures;

    // 1. Lire 5 températures avec push_back()

    // 2. Afficher le vector

    // 3. Trouver min, max et moyenne

    // 4. Supprimer le dernier élément avec pop_back()

    // 5. Réafficher

    return 0;
}
```

Solution : [exercise.cpp](exercise.cpp). Points à retenir :

- `push_back()` dans une boucle pour remplir le `vector`, `pop_back()` pour retirer le dernier élément ;
- `std::min_element` / `std::max_element` retournent des **itérateurs**, d'où le `*` pour obtenir la valeur ;
- `std::accumulate` (de `<numeric>`) somme les éléments. On part de `0.0` (un `double`) pour que la moyenne ne soit pas tronquée par une division entière ;
- le paramètre de `print` est une `const std::vector<int> &` : pas de copie, et la fonction ne peut pas modifier le conteneur.

**Bonus si tu termines avant les 12 minutes :** remplace `std::vector` par `std::deque` et teste `push_front()` pour ajouter une température au début.

## Constructeurs

Consultez l'exemple [constructor.cpp](constructor.cpp)