#include <iostream>
#include <iomanip>
#include "graph.cpp"

using ElemType=std::string;

void displayMenu(int index) {
    printf("----------------------------------------\n");
    printf("** Current Index is %d **\n", index);
    printf("%-20s%-20s\n", "1. Init", "10. DeleteArc");
    printf("%-20s%-20s\n", "2. Destroy", "11. DFSTraverse");
    printf("%-20s%-20s\n", "3. LocateVex", "12. BFSTraverse");
    printf("%-20s%-20s\n", "4. AssignVex", "15. Save");
    printf("%-20s%-20s\n", "5. FirstAdjVex", "16. Load");
    printf("%-20s%-20s\n", "6. NextAdjVex", "20. ChangeIndex");
    printf("%-20s%-20s\n", "7. InsertVex ", "");
    printf("%-20s%-20s\n", "8. DeleteVex", "");
    printf("%-20s%-20s\n", "9. InsertArc", "");
}

int main() {
    auto option = 1;
    auto index = 0;
    GraphHead<ElemType> lists[20];
    while (option) {
        try {
            displayMenu(index);
            std::cin >> option;
            switch (option) {
                case 0: {
                    break;
                }
                case 1: {
                    lists[index] = GraphHead<ElemType>();
                    std::cout << "Init" << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Destroy" << std::endl;
                    lists[index].clear();
                    break;
                }
                case 3: {
                    nodeKey key;
                    std::cout << "LocateNode" << std::endl;
                    std::cout << "Input key:" << std::endl;
                    std::cin >> key;
                    std::cout << "Value:" << lists[index].locate(key).val() << std::endl;
                    break;
                }
                case 4: {
                    nodeKey key;
                    ElemType val;
                    std::cout << "Assign" << std::endl;
                    std::cout << "Input key and value:" << std::endl;
                    std::cin >> key >> val;
                    lists[index].assignVex(key, val);
                    break;
                }
                case 5: {
                    nodeKey key;
                    std::cout << "FirstAdjVex" << std::endl;
                    std::cout << "Input key:" << std::endl;
                    std::cin >> key;
                    std::cout << lists[index].firstAdjVex(key) << std::endl;
                    break;
                }
                case 6: {
                    nodeKey key, adjKey;
                    std::cout << "NextAdjVex" << std::endl;
                    std::cout << "Input Node key and Adjacency key:" << std::endl;
                    std::cin >> key >> adjKey;
                    std::cout << lists[index].nextAdjVex(key, adjKey) << std::endl;
                    break;
                }
                case 7: {
                    nodeKey key;
                    ElemType val;
                    std::cout << "InsertVex" << std::endl;
                    std::cout << "Input key and value:" << std::endl;
                    std::cin >> key >> val;
                    lists[index].insertVex(GraphNode<ElemType>(key, val));
                    break;
                }
                case 8: {
                    nodeKey key;
                    std::cout << "DeleteVex" << std::endl;
                    std::cout << "Input key:" << std::endl;
                    std::cin >> key;
                    lists[index].removeVex(key);
                    break;
                }
                case 9: {
                    nodeKey firKey, secKey;
                    std::cout << "InsertArc" << std::endl;
                    std::cout << "Input firKey and secKey:" << std::endl;
                    std::cin >> firKey >> secKey;
                    lists[index].insertArc(firKey, secKey);
                    break;
                }
                case 10: {
                    nodeKey firKey, secKey;
                    std::cout << "DeleteArc" << std::endl;
                    std::cout << "Input firKey and secKey:" << std::endl;
                    std::cin >> firKey >> secKey;
                    lists[index].removeArc(firKey, secKey);
                    break;
                }
                case 11: {
                    std::cout << "DFSTraverse" << std::endl;
                    lists[index].DFSTraverse([](GraphNode<ElemType> &node) {
                        std::cout << "Key: " << node.key() << " Val: " << node.val() << " Adjacency Key:";
                        node.traverse([](VexNode &vexNode) {
                            std::cout << vexNode.key() << " ";
                        });
                        std::cout << std::endl;
                    });
                    break;
                }
                case 12: {
                    std::cout << "DFSTraverse" << std::endl;
                    lists[index].BFSTraverse([](GraphNode<ElemType> &node) {
                        std::cout << "Key: " << node.key() << " Val: " << node.val() << " Adjacency Key:";
                        node.traverse([](VexNode &vexNode) {
                            std::cout << vexNode.key() << " ";
                        });
                        std::cout << std::endl;
                    });
                    break;
                }
//                case 15: {
//                    std::cout << "Save" << std::endl;
//                    lists[index].save(std::to_string(index));
//                    break;
//                }
//                case 16: {
//                    std::cout << "Load" << std::endl;
//                    lists[index].clear();
//                    lists[index].load(std::to_string(index));
//                    break;
//                }
//                case 20 : {
//                    std::cout << "ChangeIndex" << std::endl;
//                    std::cin >> index;
//                    continue;
//                }
                default: {
                    break;
                }
            }
        } catch (std::exception &e) {
            std::cout << "RuntimeException: " << e.what() << std::endl;
        }
    }
}
