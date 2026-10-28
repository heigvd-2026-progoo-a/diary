# Semaine 06/16

- [ ] Polymorphisme
  - [ ] Dynamique (vtables)
  - [ ] Static
    - [ ] Surcharge paramétrique
    - [ ] Templates

## Héritage

Rappelons le concept d'héritage en programmation objet. L'héritage est un mécanisme qui permet de créer une nouvelle classe à partir d'une classe existante. La nouvelle classe, appelée **classe dérivée**, hérite des membres (attributs et méthodes) de la classe existante, appelée **classe de base**. Cela permet de réutiliser le code et de créer des hiérarchies de classes et ainsi d'éviter la duplication de code.

Dans l'exemple suivant on défini une classe de base `Animal` et une classe dérivée `Cat`:

```cpp
class Animal { void eat(); }; // classe de base

class Cat : public Animal { void meow(); }; // classe dérivée
```

Tout animal peut manger, mais un chat peut en plus miauler. On peut donc créer un chat qui *hérite* de la méthode `eat` et de sa propre méthode `meow`:

```cpp
Cat cat;
cat.eat(); // hérité de Animal
cat.meow(); // défini dans Cat
```

En C++ il y a une classification de l'héritage qui permet de définir le niveau d'accès aux membres hérités. Il existe trois types d'héritage: public, protected et private. C'est assez spécifique à C++ et presque aucun autre langage de programmation propose cette granularité. Néanmoins voici ce que deviennent les membres hérités:

| Type d'héritage | public | protected | private |
|----------------|--------|-----------|---------|
| public         | public | protected | private |
| protected      | protected | protected | private |
| private        | private | private | private |

Dans la vaste majorité des cas si ce n'est le 100 pourcent du temps, l'héritage est public. Il est très rare de vouloir cacher des méthodes héritées à la classe dérivée.

## Spécificateur de fonction

En C++, il existe une syntaxe nommée "spécificateur de fonction" qui permet de définir un attachement particulier à une fonction. Il existe trois possibilités:

| Syntaxe | Nom | Signification |
|---------|-----|----------------|
| `= 0` | `pure-specifier` | Déclare une fonction virtuelle pure |
| `= default` | `explicitly-defaulted function` | Demande au compilateur de générer l'implémentation par défaut |
| `= delete` | `deleted function` | Interdit l'utilisation d'une fonction |

Par exemple

```cpp
class Animal {
public:
    Animal() = default;
    Animal(const Animal&) = delete;

    virtual void sleep() = 0;
};
```

Dans cette classe on supprime volontairement le comportement par défaut du constructeur de copie. Cela signifie que l'on ne peut pas copier un objet de type `Animal`. Le constructeur par défaut est explicitement noté comme tel. Enfin le plus étrange des trois, c'est le `= 0` qui n'est autorisé que coinjointement avec le mot clé `virtual`.

Il dit que la méthode `sleep` n'a pas le droit d'exister pas dans la classe `Animal` mais qu'elle doit exister quand même pour chaque animal. Un `Animal` est donc une classe abstraite car elle ne peut pas être instanciée (`Animal a;` est interdit, car un de ses comportement n'est pas défini). À quoi est-ce que cela sert ?

C'est très utile lors de l'héritage, mais avant de voir cela nous devons définir ce qu'est une interface.

## Fonctions virtuelles

En C++, le mot clé `virtual` peut être utilisé devant une méthode pour indiquer que cette méthode est spéciale. Si l'on s'interesse à l'étymologie, *Virtuel* vient du latin scolastique *virtualis*, dérivé de *virtus* : la force, la capacité de produire un effet. Chez les scolastiques héritiers d'Aristote, est virtuel ce qui existe en puissance et non en acte:

> Le gland contient virtuellement le chêne : le chêne n'est pas encore là, mais tout ce qu'il faut pour qu'il advienne l'est.

En pratique, déclarer une méthode virtuelle pure, ici `eat`, signifie que l'on ne sait pas comment un animal mange, mais que l'on sait qu'il mange. On peut donc déclarer une méthode `feed` qui prend un animal et lui demande de manger. Le comportement concret de la méthode `eat` sera défini dans les classes dérivées:

```cpp
struct Animal {
    virtual void eat() = 0;   // capacité déclarée, jamais actualisée ici
};

struct Cat : Animal {
    void eat() override { /* actualisation concrète */ }
};

void feed(Animal& a) { a.eat(); }  // l'appel est en puissance
```

On utilise volontiers à partir de C++11 le mot clé `override` qui n'a aucun autre effet que de signaler à l'utilisateur que la méthode `eat` est une surcharge d'une méthode virtuelle de la classe de base. Si `eat` n'est pas virtuelle dans la classe de base, le compilateur émettra une erreur. Cela permet d'éviter des erreurs de surcharge par inadvertance.

### Fonctionnement interne des fonctions virtuelles

On peut se demander quel est la nécessité de devoir déclarer une méthode vérituelle, on pourrait très bien écrire:

```cpp
struct Animal {
    void eat() { std::cout << "Animal eats" << std::endl; }
};

struct Cat : Animal {
    void eat() { std::cout << "Cat eats" << std::endl; }
};

void feed(Animal& a) { a.eat(); }
```

Or du point de vue du compilateur, au moment de la traduction du C++ en assembleur il sait:

1. Que `feed` prend une référence vers un `Animal` en paramètre
2. Que `Animal` a une méthode `eat`

Il n'est pas en capacité de déduire que l'objet passé est en fait un `Cat`. En mémoire l'instance de `Cat` n'est qu'une adresse mémoire sans contenu. Le compilateur n'a pas le choix que d'appeler l'implémentation `Animal::eat` et non `Cat::eat`:

```cpp
Cat cat;
feed(cat); // affiche "Animal eats"
```

En revanche, si la méthode `eat` est déclarée virtuelle, le compilateur va générer un mécanisme de dispatch dynamique. Il va créer une table de pointeurs de fonctions (*vtables*) qui va contenir les adresses des méthodes virtuelles. Chaque classe dérivée aura sa propre vtable. Ainsi, lorsque l'on appelle `a.eat()`, le programme va regarder dans la vtable de l'objet réel (ici `Cat`) pour trouver l'adresse de la méthode à exécuter.

Lorsque la méthode d'un objet contenant des méthodes virtuelles est appelées, plutôt que de directement exécuter la méthode correspondante, le programme va chercher dans la vtable de l'objet pour trouver l'adresse de la méthode à exécuter. Cela permet d'avoir un comportement **polymorphe**, où le même appel de méthode peut avoir des comportements différents selon le type réel de l'objet :

```cpp
struct Animal {
    virtual void eat() { std::cout << "Animal eats" << std::endl; }
};

struct Cat : Animal {
    void eat() override { std::cout << "Cat eats" << std::endl; }
};

// Le dispatch est ici dynamique. Il coûte deux indirections mémoire:
// 1. On récupère l'adresse de la vtable de l'objet
// 2. On récupère l'adresse de la méthode à exécuter dans la vtable (Cat::eat())
void feed(Animal& a) { a.eat(); }
```

Et donc :

```cpp
Cat cat;
feed(cat); // affiche "Cat eats"
```

## Interfaces

En programmation orientée objet, une interface est un type de classe qui définit un ensemble de méthodes que les classes dérivées doivent implémenter. C'est une sorte de contrat qui garantit que les classes qui réalisent l'interface respectent un certain comportement. C'est notament utile lorsque plusieurs étuipees de développemnt travaille sur un projet et doivent s'aligner sur un comportement commun.

Imaginons que nous réalisons un logiciel qui doit pouvoir imprimer des documents. Imaginons aussi un fabricant d'imprimante. Quelle est l'interface entre ces deux entités ? Le logiciel doit pouvoir envoyer l'ordre d'impression à l'imprimante qui doit lui offrir une méthode pour recevoir cet ordre. De la même manière une imprimante peut avoir différents format de papier, le logiciel peut demander quels sont les formats supportés et elle doit pouvoir changer le format par exemple. L'interface serait donc la suivante:

```cpp
struct Printer {
    virtual void print(const Document& doc) = 0;
    virtual std::vector<PaperFormat> getSupportedFormats() = 0;
    virtual void setPaperFormat(PaperFormat format) = 0;
};
```

Il y a deux éléments nouveau. D'une part le mot clé `virtual`, mais aussi le `= 0` à la fin de chaque méthode.
