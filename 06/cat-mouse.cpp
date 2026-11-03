#include <iostream>
#include <vector>

using namespace std;

struct IAnimal {
    virtual void eat() = 0;
    virtual void sleep() = 0;
};

struct Cat : public IAnimal {
    int a;
    void eat() override{ cout << "Cat is eating\n"; }
    void sleep() override{ cout << "Cat is sleeping\n"; }
};

struct Mouse : public IAnimal {
    double b;
    void eat()override { cout << "Mouse is eating\n"; }
    void sleep() override{ cout << "Mouse is sleeping\n"; }
};

int main() {
    vector<IAnimal*> zoo;
    zoo.push_back(new Mouse());
    zoo[0]->eat();
}