#include <iostream>
#include "SeqList.cpp"

typedef std::string ElemType;

void displayMenu(int index) {
    printf("----------------------------------------\n");
    printf("** Current Index is %d **\n", index);
    printf("%-20s%-20s\n", "1. InitList", "10. ListInsert");
    printf("%-20s%-20s\n", "2. DestroyList", "11. ListDelete");
    printf("%-20s%-20s\n", "3. ClearList", "12. ListTraverse");
    printf("%-20s%-20s\n", "4. ListEmpty", "13. Push");
    printf("%-20s%-20s\n", "5. ListLength", "14. Pop");
    printf("%-20s%-20s\n", "6. GetElem", "15. Save");
    printf("%-20s%-20s\n", "7. LocateElem", "16. Load");
    printf("%-20s%-20s\n", "8. PriorElem", "20. ChangeIndex");
    printf("%-20s%-20s\n", "9. NextElem", "");
}

int main() {
    int option = 1;
    int index = 0;
    List<ElemType> lists[20];
    while (option) {
        try {
            displayMenu(index);
            std::cin >> option;
            switch (option) {
                case 0: {
                    break;
                }
                case 1: {
                    lists[index] = List<ElemType>(0);
                    std::cout << "InitList" << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "DestroyList" << std::endl;
                    lists[index].clear();
                    std::ofstream os(std::to_string(index), std::ios_base::out | std::ios_base::trunc);
                    break;
                }
                case 3: {
                    std::cout << "ClearList" << std::endl;
                    lists[index].clear();
                    std::ofstream os(std::to_string(index), std::ios_base::out | std::ios_base::trunc);
                    break;
                }
                case 4: {
                    std::cout << "ListEmpty" << std::endl;
                    std::cout << (lists[index].size() ? "False" : "True") << std::endl;
                    break;
                }
                case 5: {
                    std::cout << "ListLength" << std::endl;
                    std::cout << lists[index].length() << std::endl;
                    break;
                }
                case 6: {
                    std::cout << "GetElem" << std::endl;
                    int i = 0;
                    std::cin >> i;
                    std::cout << lists[index].get(i) << std::endl;
                    break;
                }
                case 7: {
                    std::cout << "LocateElem" << std::endl;
                    ElemType i;
                    std::cin >> i;
                    std::cout << lists[index].locate(i, [](const ElemType &a, const ElemType &b) -> bool {
                        return a == b;
                    }) << std::endl;
                    break;
                }
                case 8: {
                    std::cout << "PriorElem" << std::endl;
                    ElemType i;
                    std::cin >> i;
                    std::cout << lists[index].prior(i) << std::endl;
                    break;
                }
                case 9: {
                    std::cout << "NextElem" << std::endl;
                    ElemType i;
                    std::cin >> i;
                    std::cout << lists[index].next(i) << std::endl;
                    break;
                }
                case 10: {
                    std::cout << "listsInsert" << std::endl;
                    int i = 0;
                    ElemType v;
                    std::cin >> i;
                    std::cin >> v;
                    lists[index].insert(i, v);
                    break;
                }
                case 11: {
                    std::cout << "ListDelete" << std::endl;
                    int i = 0;
                    std::cin >> i;
                    std::cout << lists[index].remove(i) << std::endl;
                    break;
                }
                case 12: {
                    std::cout << "ListTraverse" << std::endl;
                    lists[index].traverse([](const ElemType &e) -> void { std::cout << e << std::endl; });
                    std::cout << std::endl;
                    break;
                }
                case 13: {
                    std::cout << "Push" << std::endl;
                    ElemType v;
                    std::cin >> lists[index];
                    break;
                }
                case 14: {
                    std::cout << "Pop" << std::endl;
                    ElemType v = lists[index].remove(lists->length());
                    std::cout << v << std::endl;
                    break;
                }
                case 15: {
                    std::cout << "Save" << std::endl;
                    lists[index].save(std::to_string(index) + ".sav");
                    break;
                }
                case 16: {
                    std::cout << "Load" << std::endl;
                    lists[index].clear();
                    lists[index].load(std::to_string(index) + ".sav");
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