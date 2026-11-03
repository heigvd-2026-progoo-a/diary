#include <iostream>
using namespace std;

struct A {
    A() { cout << "A()\n"; }
    ~A() { cout << "~A()\n"; }
};

struct B : public virtual A {
    B() { cout << "B()\n"; }
    ~B() { cout << "~B()\n"; }
};

struct C : public virtual A {
    C() { cout << "C()\n"; }
    ~C() { cout << "~C()\n"; }
};

struct D : public B, public C {
    D() { cout << "D()\n"; }
    ~D() { cout << "~D()\n"; }
};

int main() { D d; }