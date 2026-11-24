




struct C {
    C() {}           // Constructeur par défaut
    C(C& other) {}   // Constructeur par copie
    C(C&& other) {}  // Constructeur par déplacement
};

int main() {
    C u;
    C v(std::move(u));
}