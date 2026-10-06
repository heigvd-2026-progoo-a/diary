#include <vector>
#include <deque>
#include <iostream>

int main() {
    std::deque<int> v;

    v.push_back(4);
    v.push_back(8);
    v.push_back(15);
    v.push_back(16);
    v.push_back(23);
    v.push_back(42);

    v.pop_back();

    std::cout << "Size: " << v.size() << std::endl;
    //std::cout << "Capacity: " << v.capacity() << std::endl;

    for (auto u: v) std::cout << u << " ";
}