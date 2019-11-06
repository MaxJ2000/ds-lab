#include <iostream>
#include <iomanip>
#include "BiTree.cpp"

using ElemType=std::string;

void displayMenu(int index) {
    printf("----------------------------------------\n");
    printf("** Current Index is %d **\n", index);
    printf("%-20s%-20s\n", "1. Init", "10. DeleteNode");
    printf("%-20s%-20s\n", "2. Destroy", "11. PreOrderTraverse");
    printf("%-20s%-20s\n", "3. Clear", "12. InOrderTraverse");
    printf("%-20s%-20s\n", "4. Empty", "13. PostOrderTraverse");
    printf("%-20s%-20s\n", "5. Depth", "14. LevelOrderTraverse");
    printf("%-20s%-20s\n", "6. LocateElem", "15. Save");
    printf("%-20s%-20s\n", "7. Assign ", "16. Load");
    printf("%-20s%-20s\n", "8. GetSibling", "20. ChangeIndex");
    printf("%-20s%-20s\n", "9. InsertNode", "");
}

int main() {
    auto option = 1;
    auto index = 0;
    TreeHead<ElemType> lists[20];
    while (option) {
        try {
            displayMenu(index);
            std::cin >> option;
            switch (option) {
                case 0: {
                    break;
                }
                case 1: {
                    lists[index] = TreeHead<ElemType>();
                    std::cout << "Init" << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Destroy" << std::endl;
                    lists[index].clear();
                    break;
                }
                case 3: {
                    std::cout << "Clear" << std::endl;
                    lists[index].clear();
                    break;
                }
                case 4: {
                    std::cout << "Empty" << std::endl;
                    std::cout << (lists[index].empty() ? "True" : "False") << std::endl;
                    break;
                }
                case 5: {
                    std::cout << "Depth" << std::endl;
                    std::cout << lists[index].depth() << std::endl;
                    break;
                }
                case 6: {
                    nodeKey key;
                    std::cout << "LocateNode" << std::endl;
                    std::cout << "Input key:" << std::endl;
                    std::cin >> key;
                    std::cout << lists[index].locate(key) << std::endl;
                    break;
                }
                case 7: {
                    nodeKey key;
                    ElemType val;
                    std::cout << "Assign" << std::endl;
                    std::cout << "Input key and value:" << std::endl;
                    std::cin >> key >> val;
                    lists[index].assign(key, val);
                    break;
                }
                case 8: {
                    nodeKey key;
                    std::cout << "GetSibling" << std::endl;
                    std::cout << "Input key:" << std::endl;
                    std::cin >> key;
                    auto node = lists[index].getSibling(key);
                    if (node == nullptr) {
                        std::cout << "Bad key!";
                    } else {
                        std::cout << "Target Key:" << node->key() << std::endl;
                        std::cout << "Target Value:" << node->val() << std::endl;
                    }
                    break;
                }
                case 9: {
                    nodeKey key, insertKey;
                    ElemType val;
                    bool pos;
                    std::cout << "InsertNode" << std::endl;
                    std::cout << "Input Target's key:" << std::endl;
                    std::cin >> key;
                    std::cout << "Input where to insert(0 to left,1 to right):" << std::endl;
                    std::cin >> pos;
                    std::cout << "Input Node's key and value:" << std::endl;
                    std::cin >> insertKey >> val;
                    lists[index].insert(key, pos, std::make_unique<TreeNode<ElemType >>(insertKey, val));
                    break;
                }
                case 10: {
                    nodeKey key;
                    std::cout << "DeleteNode" << std::endl;
                    std::cout << "Input key:" << std::endl;
                    std::cin >> key;
                    std::cout << "Target value:" << lists[index].deleteNode(key)->val() << std::endl;
                    break;
                }
                case 11: {
                    std::cout << "PreOrderTraverse" << std::endl;
                    lists[index].preOrderTraverse([](const nodeKey &key, const ElemType &val) {
                        std::cout << std::left << std::setw(20) << key << val << std::endl;
                    });
                    break;
                }
                case 12: {
                    std::cout << "inOrderTraverse" << std::endl;
                    lists[index].inOrderTraverse([](const nodeKey &key, const ElemType &val) {
                        std::cout << std::left << std::setw(20) << key << val << std::endl;
                    });
                    break;
                }
                case 13: {
                    std::cout << "postOrderTraverse" << std::endl;
                    lists[index].postOrderTraverse([](const nodeKey &key, const ElemType &val) {
                        std::cout << std::left << std::setw(20) << key << val << std::endl;
                    });
                    break;
                }
                case 14: {
                    std::cout << "levelOrderTraverse" << std::endl;
                    lists[index].levelOrderTraverse([](const nodeKey &key, const ElemType &val) {
                        std::cout << std::left << std::setw(20) << key << val << std::endl;
                    });
                    break;
                }
                case 15: {
                    std::cout << "Save" << std::endl;
                    lists[index].save(std::to_string(index));
                    break;
                }
                case 16: {
                    std::cout << "Load" << std::endl;
                    lists[index].clear();
                    lists[index].load(std::to_string(index));
                    break;
                }
                case 20 : {
                    std::cout << "ChangeIndex" << std::endl;
                    std::cin >> index;
                    continue;
                }
                default: {
                    break;
                }
            }
        } catch (std::exception &e) {
            std::cout << "RuntimeException: " << e.what() << std::endl;
        }
    }
}
