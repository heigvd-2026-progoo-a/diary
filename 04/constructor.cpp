#include <vector> 
#include <iostream>

class Class {
    int value;
  public:
    Class(): value(42) {}
    Class(int v) : value(v) { }
    Class(int v, int w): value(v + w) { } 

    int getValue() const { return value; }
};

int main() {
    std::vector<Class> collection;

    Class a; // Appelle le constructeur par défaut
    Class b(23); // Appelle le constructeur avec un paramètre
    Class c(8, 15); // Appelle le constructeur avec deux paramètres

    collection.push_back(a);
    collection.push_back(b);
    collection.push_back(c);
    for (auto c : collection) { std::cout << c.getValue() << ' '; }
}