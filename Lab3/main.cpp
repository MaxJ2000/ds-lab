#include <iostream>
#include "BiTree.cpp"

int main() {
    std::vector<std::string> a{"2333", "B", "C", "D", "E", "F"};
    std::vector<std::string> b{"C", "B", "D", "2333", "F", "E"};
    std::vector<std::string> c{"1", "2", "3", "4", "5", "6"};
    TreeHead<std::string> test(a, b, c);
    test.inOrderTraverse([](const nodeKey &key, const std::string &val) {
        std::cout << key << "    " << val << std::endl;
    });
//    test.preOrderTraverse([](const nodeKey &key, const std::string &val) {
//        std::cout << key;
//    });
//    test.postOrderTraverse([](const nodeKey &key, const std::string &val) {
//        std::cout << key;
//    });
//    test.levelOrderTraverse([](const nodeKey &key, const std::string &val) {
//        std::cout << key;
//    });
    std::cout << test.depth();
    test.load("0");
    auto d = test.deleteNode("A").get();
    getchar();
    return 0;
}