#include <iostream>
#include <cstring>

class C {
    int *data;
    size_t size; // C'est unsigned long long

  public:
    C(size_t size) : size(size) {
        if (size < 100) 
            data = new int[size];
    };

    C(const C &other) {
        // 1. Créer un nouvel espace mémoire
        data = new int[size];

        // 2. Copier les données
        std::memcpy(data, other.data, size);
    }

    C operator=(const C &other) {
        size = other.size;
        data = other.data;
    }
    
    ~C() { free(data); }
};

int main() {
    C c{};
}