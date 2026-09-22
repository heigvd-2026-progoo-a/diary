# Semaine 01/16

- [ ] C++ c'est un superset de C
- [ ] Inventé par Bjarne Stroustrup en 1979
- [ ] Normalisé ISO en 1998 (ISO/IEC 14882:1998)
- [ ] Superset oui, mais pas totalement compatible avec C
- [ ] C++ il apporte le paradigme objet
- [ ] Les 6 étages de la programmation orientée objet
   1. Objet
   2. Classe
   3. Héritage
   4. Polymorphisme
   5. Abstraction
   6. Encapsulation
- [ ] Namespace `std::` (standard)
- [ ] La référence C++ (https://en.cppreference.com/w/)

## Ecrire sur la sortie standard

```cpp
#include <iostream>

int main() {
    std::cout << "Hello World!" << std::endl;
    return 0;
}
```

## Lire depuis l'entrée standard

```cpp
#include <iostream>

int main() {
    int age;
    std::cout << "Quel âge avez-vous ? ";
    std::cin >> age;
    std::cout << "Vous avez " << age << " ans." << std::endl;
    return 0;
}
```

## Configurer le nombre de digits et padding

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159265358979323846;
    std::cout.precision(5);
    std::cout << "Pi avec 5 chiffres significatifs : " << pi << std::endl;
    std::cout.width(10);
    std::cout << "Pi avec padding : " << pi << std::endl;

    // setprecision + fixed (printf("%.2f", pi))
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Pi avec 2 chiffres après la virgule : " << pi << std::endl;

    // setw (printf("%10.2f", pi))
    std::cout << std::setw(10) << pi << std::endl;
}§
```