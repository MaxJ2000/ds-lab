#include <iostream>
#include "BiTree.cpp"

int main() {
    std::vector<std::string> a{"A", "B", "C", "D", "E", "F"};
    std::vector<std::string> b{"C", "B", "D", "A", "F", "E"};
    TreeHead<std::string> test(a, b);
    test.inOrderTraverse([](const nodeKey &key, const std::string &val) {
        std::cout << key;
    });
    test.preOrderTraverse([](const nodeKey &key, const std::string &val) {
        std::cout << key;
    });
    test.postOrderTraverse([](const nodeKey &key, const std::string &val) {
        std::cout << key;
    });
    test.levelOrderTraverse([](const nodeKey &key, const std::string &val) {
        std::cout << key;
    });
    std::cout << test.depth();
    auto d = test.deleteNode("A").get();
    getchar();
    return 0;
}