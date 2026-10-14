
struct Foo {
    char i;
    Foo(char i) : i{i} {}
};

int main(int argc, char*argv[]) {
    Foo f{argc};
}