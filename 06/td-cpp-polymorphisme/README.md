# Interfaces et composition d'interfaces en C++

Ce dépôt contient le travail dirigé consacré aux interfaces en C++. Lors de la séance précédente, vous avez modélisé des animaux par une hiérarchie de classes : `Cat` et `Mouse` héritent d'une classe abstraite `Animal`. Ce modèle décrit bien *ce qu'est* un objet, mais il ne dit rien de *ce qu'il sait faire*. Or chasser, être capturé, émettre un son ou se laisser caresser sont des capacités qui traversent la taxonomie : un détecteur de fumée émet un son sans être un animal, et un chat se laisse caresser alors qu'une souris ne le fait pas.

L'objectif de la séance est de remplacer cette modélisation fondée sur l'identité par une modélisation fondée sur les capacités. Vous apprendrez à déclarer une interface C++ correcte, à en faire implémenter plusieurs par une même classe, à composer une interface à partir d'une autre et à écrire des fonctions qui ne dépendent que de la capacité dont elles ont besoin.

L'énoncé complet, avec les explications théoriques, les consignes détaillées et les questions de réflexion, se trouve dans [td-interfaces.md](td-interfaces.md) et dans sa version PDF.

## Ce que l'on attend de vous

Vous travaillez en binôme sur le fichier [depart/zoo.cpp](depart/zoo.cpp), que vous faites évoluer en quatre étapes d'environ cinq minutes chacune. À la fin de chaque étape, votre programme doit compiler sans avertissement et s'exécuter correctement ; ne passez jamais à l'étape suivante avec un programme cassé.

À la première étape, vous déclarez trois interfaces, `ISoundEmitter`, `IPrey` et `IPredator`. À la deuxième, vous les faites implémenter par `Cat` et `Mouse`, puis vous écrivez une fonction `concert` et faites chasser le chat. À la troisième, vous composez une interface `IPet` à partir d'`ISoundEmitter` et l'utilisez dans une fonction `petCorner`. À la quatrième, vous ajoutez une chouette et un détecteur de fumée **sans modifier une seule ligne** de `concert`, `petCorner`, `Cat` ou `Mouse` : c'est le critère de réussite du travail. Un exercice bonus sur le problème du diamant attend ceux qui terminent en avance.

Le programme final doit produire exactement la sortie suivante :

```text
BIIIP Miaou Couic Hou hou Couic
Felix attrape une proie
Felix attrape une proie
BIIIP Miaou ... Hou hou ...
Felix ronronne (Miaou)
```

## Compiler et exécuter

Compilez toujours avec les avertissements complets, afin que le compilateur signale la moindre faute de signature :

```bash
g++ -std=c++17 -Wall -Wextra -pedantic depart/zoo.cpp -o zoo && ./zoo
```

Le `Makefile` automatise la compilation du code de départ et des corrigés :

```bash
make        # compile tous les programmes dans build/
make run    # les exécute l'un après l'autre
make pdf    # produit l'énoncé build/td-interfaces.pdf
make clean  # supprime build/
```

La génération du PDF repose sur [TeXSmith](https://pypi.org/project/texsmith/) ; les dépendances Python sont décrites dans `pyproject.toml` et installées par `uv sync`.

## Organisation du dépôt

Le répertoire [depart/](depart/) contient le code dont vous partez. Le répertoire [corrige/](corrige/) contient un corrigé autonome par étape (`etape1.cpp` à `etape4.cpp`) ainsi que celui du bonus (`bonus.cpp`). Résistez à la tentation de les consulter avant d'avoir sérieusement cherché : l'intérêt de la séance réside dans les erreurs du compilateur que vous rencontrerez et comprendrez par vous-mêmes. Le répertoire [fragments/](fragments/) contient la mise en page HEIG-VD utilisée par TeXSmith pour produire le PDF.
