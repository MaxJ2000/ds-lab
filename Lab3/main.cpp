#include <iostream>
#include "BiTree.cpp"

int main() {
    TreeHead<std::string> test("ABCDEF", "CBDAFE");
    std::cout<<test.locate(4);
    return 0;
}