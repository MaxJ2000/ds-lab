#include <iostream>
#include "List.cpp"

int main() {
    ListHead<std::string> test;
    test.insert("test");
    test.insert("2333");
    test.insert("???");
    for (auto &&i:test) {
        std::cout << i;
    }
}
