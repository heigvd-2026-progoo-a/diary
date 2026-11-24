


struct Singleton {
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& get_instance() {
        static Singleton instance;
        return instance;
    }
    private:
    Singleton() = default;
};


int main() {
    auto u = Singleton::get_instance();

    Singleton u;
    Singleton v;


}