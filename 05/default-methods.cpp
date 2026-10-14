#include <iostream>
using namespace std; // from std import *

struct Class {
    char name;

    // Constructeur par défaut
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

    // Destructeur par défaut
    ~Class() {
        cout << "Class " << name << " a été détruit\n";
    }
};


int main() {
    Class c('c');
    Class d('d');
    d = c;
}
