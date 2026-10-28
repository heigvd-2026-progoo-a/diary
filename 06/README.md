# Semaine 06/16

- [x] Interfaces
- [x] Méthodes virtuelles
- [x] Polymorphisme
  - [x] Dynamique (vtables)
  - [x] Statique
    - [x] Surcharge (ad hoc)
    - [x] Templates (paramétrique)

## Héritage

Rappelons le concept d'héritage en programmation orientée objet. L'héritage permet de créer une nouvelle classe à partir d'une classe existante. La nouvelle classe, appelée **classe dérivée**, hérite des membres (attributs et méthodes) de la classe existante, appelée **classe de base**. On réutilise ainsi le code existant, on évite de le dupliquer et on organise les classes en hiérarchies.

Dans l'exemple suivant, on définit une classe de base `Animal` et une classe dérivée `Cat` :

```cpp
class Animal {               // classe de base
public:
    void eat();
};

class Cat : public Animal {  // classe dérivée
public:
    void meow();
};
```

Tout animal peut manger, mais un chat peut en plus miauler. Un `Cat` *hérite* donc de la méthode `eat` d'`Animal` et possède en plus sa propre méthode `meow` :

```cpp
Cat cat;
cat.eat();  // hérité de Animal
cat.meow(); // défini dans Cat
```

> Attention : dans une `class`, les membres sont `private` par défaut. Sans le `public:`, l'appel `cat.eat()` serait refusé par le compilateur.

En C++, on précise un **type d'héritage** (`public`, `protected` ou `private`) qui détermine ce que deviennent, dans la classe dérivée, les membres hérités. C'est assez spécifique au C++ : presque aucun autre langage ne propose cette granularité. Le tableau se lit ainsi : la ligne indique le type d'héritage, la colonne le niveau d'accès du membre dans la classe de base.

| Type d'héritage | membre `public` | membre `protected` | membre `private` |
|-----------------|-----------------|--------------------|------------------|
| `public`        | public          | protected          | inaccessible     |
| `protected`     | protected       | protected          | inaccessible     |
| `private`       | private         | private            | inaccessible     |

Notez que les membres `private` de la classe de base ne sont **jamais** accessibles depuis la classe dérivée, quel que soit le type d'héritage : ils existent bien dans l'objet, mais seule la classe de base peut y toucher.

Dans la très grande majorité des cas, l'héritage est `public` : un `Cat` *est un* `Animal` et doit offrir au monde extérieur tout ce qu'offre un `Animal`. Il est très rare de vouloir cacher aux utilisateurs de la classe dérivée les méthodes qu'elle a héritées.

## Spécificateurs de fonction

En C++, on peut terminer la déclaration d'une méthode par une indication spéciale qui modifie son statut. Il existe trois possibilités :

| Syntaxe     | Nom (norme C++)                 | Signification                                                  |
|-------------|---------------------------------|----------------------------------------------------------------|
| `= 0`       | *pure-specifier*                | Déclare une méthode virtuelle pure (sans implémentation ici)   |
| `= default` | *explicitly-defaulted function* | Demande au compilateur de générer l'implémentation par défaut  |
| `= delete`  | *deleted function*              | Interdit l'utilisation de la fonction                          |

Par exemple :

```cpp
class Animal {
public:
    Animal() = default;
    Animal(const Animal&) = delete;

    virtual void sleep() = 0;
};
```

Dans cette classe :

- le constructeur par défaut est explicitement demandé au compilateur (`= default`) ;
- le constructeur de copie est volontairement supprimé (`= delete`) : on ne peut pas copier un `Animal` ;
- la méthode `sleep` est déclarée avec `= 0`. C'est le plus étrange des trois, et il n'est autorisé que conjointement avec le mot-clé `virtual`.

Le `= 0` signifie que la méthode `sleep` n'a **pas d'implémentation** dans la classe `Animal`, mais que tout animal concret devra en fournir une. Comme un de ses comportements n'est pas défini, `Animal` ne peut pas être instanciée : `Animal a;` est interdit. On dit que `Animal` est une **classe abstraite**.

À quoi cela sert-il ? C'est très utile avec l'héritage, mais il faut d'abord comprendre ce que signifie le mot-clé `virtual`.

## Fonctions virtuelles

En C++, le mot-clé `virtual` placé devant une méthode indique que cette méthode est spéciale : elle pourra être **redéfinie** par les classes dérivées, et c'est la version de la classe réelle de l'objet qui sera appelée.

Un détour par l'étymologie éclaire le choix du mot. *Virtuel* vient du latin scolastique *virtualis*, dérivé de *virtus* : la force, la capacité de produire un effet. Chez les scolastiques héritiers d'Aristote, est virtuel ce qui existe en puissance et non en acte :

> Le gland contient virtuellement le chêne : le chêne n'est pas encore là, mais tout ce qu'il faut pour qu'il advienne l'est.

En pratique, déclarer `eat` comme méthode virtuelle pure signifie que l'on ne sait pas *comment* un animal mange, mais que l'on sait *qu'il* mange. On peut donc écrire une fonction `feed` qui reçoit n'importe quel animal et lui demande de manger. Le comportement concret de `eat` sera défini dans les classes dérivées :

```cpp
struct Animal {
    virtual void eat() = 0;   // capacité déclarée, jamais actualisée ici
};

struct Cat : Animal {
    void eat() override { /* actualisation concrète */ }
};

void feed(Animal& a) { a.eat(); }  // l'appel est « en puissance »
```

Depuis C++11, on ajoute volontiers le mot-clé `override` après une méthode qui **redéfinit** une méthode virtuelle de la classe de base. Il rend l'intention explicite pour le lecteur, et surtout il permet au compilateur de vérifier : si la classe de base ne contient aucune méthode virtuelle de même signature (faute de frappe dans le nom, paramètre différent, `virtual` oublié…), le compilateur émet une erreur au lieu de créer silencieusement une nouvelle méthode.

> Vocabulaire : ne confondez pas **redéfinition** (*override*, remplacer dans une classe dérivée une méthode virtuelle de la base) et **surcharge** (*overload*, plusieurs fonctions de même nom avec des paramètres différents, voir plus bas).

### Fonctionnement interne des fonctions virtuelles

On peut se demander pourquoi il faut déclarer une méthode virtuelle. Ne pourrait-on pas simplement écrire :

```cpp
struct Animal {
    void eat() { std::cout << "Animal eats" << std::endl; }
};

struct Cat : Animal {
    void eat() { std::cout << "Cat eats" << std::endl; }
};

void feed(Animal& a) { a.eat(); }
```

Mettons-nous à la place du compilateur au moment où il traduit `feed` en assembleur. Il sait seulement :

1. que `feed` reçoit une référence vers un `Animal` ;
2. qu'`Animal` possède une méthode `eat`.

Il ne peut pas savoir quel objet sera passé à `feed` lors de l'exécution : un `Animal`, un `Cat`, ou un autre animal défini plus tard, dans un autre fichier. Concrètement, `feed` ne reçoit qu'une adresse mémoire, et rien dans l'objet n'indique son type réel. Le compilateur n'a donc pas d'autre choix que d'appeler `Animal::eat`, choisi d'après le type déclaré du paramètre :

```cpp
Cat cat;
feed(cat); // affiche "Animal eats"
```

En revanche, si la méthode `eat` est déclarée `virtual`, le compilateur met en place un mécanisme de **dispatch dynamique** :

- pour chaque classe possédant des méthodes virtuelles, il crée une **vtable** (*virtual table*), une table contenant les adresses des méthodes virtuelles de cette classe. `Animal` a sa vtable, `Cat` a la sienne ;
- chaque objet d'une telle classe contient, en plus de ses attributs, un pointeur caché vers la vtable de sa classe réelle.

Lors de l'appel `a.eat()`, le programme ne saute donc plus directement vers une fonction fixée à la compilation : il suit le pointeur de l'objet vers sa vtable, puis y lit l'adresse de la méthode à exécuter. Le même appel peut ainsi produire des comportements différents selon le type réel de l'objet : c'est un comportement **polymorphe**.

```cpp
struct Animal {
    virtual void eat() { std::cout << "Animal eats" << std::endl; }
};

struct Cat : Animal {
    void eat() override { std::cout << "Cat eats" << std::endl; }
};

// Le dispatch est ici dynamique. Il coûte deux indirections mémoire :
// 1. on lit dans l'objet l'adresse de sa vtable ;
// 2. on lit dans la vtable l'adresse de la méthode à exécuter (ici Cat::eat).
void feed(Animal& a) { a.eat(); }
```

Et donc :

```cpp
Cat cat;
feed(cat); // affiche "Cat eats"
```

## Interfaces

En programmation orientée objet, une **interface** définit un ensemble de méthodes que les classes qui la réalisent doivent implémenter. C'est une sorte de contrat : toute classe qui réalise l'interface garantit offrir ces comportements. C'est notamment utile lorsque plusieurs équipes de développement travaillent sur un même projet et doivent s'accorder sur un comportement commun.

Imaginons que nous développions un logiciel capable d'imprimer des documents, et imaginons un fabricant d'imprimantes. Quelle est l'interface entre ces deux parties ? Le logiciel doit pouvoir envoyer un ordre d'impression à l'imprimante, qui doit donc offrir une méthode pour le recevoir. De même, une imprimante accepte différents formats de papier : le logiciel doit pouvoir lui demander lesquels elle supporte, puis choisir celui à utiliser. L'interface serait donc la suivante :

```cpp
struct Printer {
    virtual void print(const Document& doc) = 0;
    virtual std::vector<PaperFormat> getSupportedFormats() = 0;
    virtual void setPaperFormat(PaperFormat format) = 0;
};
```

On retrouve ici les deux éléments vus plus haut : chaque méthode est `virtual` et se termine par `= 0`. Le C++ n'a pas de mot-clé `interface` comme Java ou C# : une interface est simplement une classe abstraite dont toutes les méthodes sont virtuelles pures. `Printer` ne fait rien par elle-même ; c'est au fabricant d'écrire une classe dérivée (par exemple `class LaserPrinter : public Printer`) qui implémente ces trois méthodes. Le logiciel, lui, ne manipule qu'un `Printer&` et fonctionne avec n'importe quelle imprimante.

## Polymorphisme

La finalité des mécanismes vus jusqu'ici est de permettre le **polymorphisme** : la capacité d'un même appel de fonction ou de méthode à se comporter différemment selon le type des objets concernés. On distingue deux familles, selon le moment où le choix de la fonction à exécuter est fait :

1. le polymorphisme **statique** : le choix est fait par le compilateur, à la compilation ;
2. le polymorphisme **dynamique** : le choix est fait pendant l'exécution du programme.

### Polymorphisme statique

Dans le cas de la **surcharge**, `add` a un comportement polymorphe : le compilateur choisit la bonne version de la fonction en fonction des types des arguments. Ce choix est fait à la compilation et ne coûte donc rien à l'exécution.

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }

int main() {
    int x = add(1, 2);        // appel de add(int, int)
    double y = add(1.0, 2.0); // appel de add(double, double)
}
```

On parle de polymorphisme **ad hoc** (latin : *pour ceci*, *à cet effet*), car il faut écrire une version spécifique pour chaque type.

Un autre cas de polymorphisme statique est le polymorphisme **paramétrique**, réalisé en C++ avec les templates. On n'écrit qu'une seule fois le code, en laissant le type en paramètre (`T`), et le compilateur génère lui-même une version par type utilisé :

```cpp
template <typename T>
T add(T a, T b) { return a + b; }

int main() {
    int x = add(1, 2);        // le compilateur génère et appelle add<int>
    double y = add(1.0, 2.0); // le compilateur génère et appelle add<double>
}
```

### Polymorphisme dynamique

Imaginons une collection d'animaux que l'on appelle un `zoo`, et que l'on veuille nourrir tous ses animaux. Le polymorphisme dynamique permet d'appeler `eat` sur chaque animal sans se soucier de son type concret : la version de `eat` réellement exécutée est déterminée à l'exécution, via la vtable, en fonction du type réel de chaque objet.

```cpp
struct Animal {
    virtual ~Animal() = default; // indispensable pour détruire via un Animal*
    virtual void eat() = 0;      // méthode virtuelle pure
};

struct Cat : Animal {
    void eat() override { std::cout << "Cat eats" << std::endl; }
};

struct Dog : Animal {
    void eat() override { std::cout << "Dog eats" << std::endl; }
};

int main() {
    std::vector<Animal*> zoo;
    zoo.push_back(new Cat());
    zoo.push_back(new Dog());

    for (Animal* animal : zoo) {
        animal->eat(); // appel polymorphe : "Cat eats" puis "Dog eats"
    }

    for (Animal* animal : zoo) {
        delete animal; // chaque new doit avoir son delete
    }
}
```

Le vecteur ne contient que des `Animal*`, mais chaque appel à `eat` exécute la bonne version. Ce choix ne peut pas être fait à la compilation : dans un vrai programme, le contenu du zoo pourrait dépendre d'une saisie de l'utilisateur ou d'un tirage aléatoire (voir [cats-dogs.cpp](cats-dogs.cpp)).
