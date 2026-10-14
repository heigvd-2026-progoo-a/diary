
template <class T>
class Array {
    T *data;
  public:
    Array(size_t size) {
        data = new T[size];
    }

    ~Array() {
        delete data;
    }
};

int main() {
    Array<int> a(42); 
}