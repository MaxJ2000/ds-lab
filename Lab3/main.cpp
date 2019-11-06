#include <iostream>
#include "BiTree.cpp"

int main() {
    std::vector<std::string> a{"A", "Bcddd", "C", "D", "E", "F"};
    std::vector<std::string> b{"C", "Bcddd", "D", "A", "F", "E"};
    TreeHead<std::string> test(a, b);
    std::cout << test.depth();
    auto d = test.deleteNode("A").get();
    getchar();
    return 0;
}