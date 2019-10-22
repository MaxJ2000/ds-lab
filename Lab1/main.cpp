#include <iostream>
#include "SeqList.cpp"

template<typename T>
auto InitList(List<T> &list) -> void;

template<typename T>
auto DestroyList(List<T> &list) -> void;

template<typename T>
auto ClearList(List<T> &list) -> void;

template<typename T>
auto ListEmpty(List<T> &list) -> bool;

template<typename T>
auto ListLength(List<T> &list) -> std::size_t;

template<typename T>
auto GetElem(List<T> &list, std::size_t index, T &e) -> void;

template<typename T>
auto LocateElem(List<T> &list, const T &e, std::function<bool(const T &, const T &)> &&eq) -> int;

template<typename T>
auto PriorElem(List<T> &list, const T &cur_e, T &pre_e) -> void;

template<typename T>
auto NextElem(List<T> &list, const T &cur_e, T &next_e) -> void;

template<typename T>
auto ListInsert(List<T> &list, std::size_t index, T &e) -> void;

template<typename T>
auto ListDelete(List<T> &list, std::size_t index, T &e) -> void;

template<typename T>
auto ListTraverse(List<T> &list, std::function<void(T &)> &&f) -> void;

auto printMenu() {
    printf("+--------------------------------------------------------------------+\n");
    printf("|             Welcome to panyue's linear list demo system!           |\n");
    printf("|               Here are some functions you can call:                |\n");
    printf("|                                                                    |\n");
    printf("|               1: init_list           2: destroy_list               |\n");
    printf("|               3: clear_list          4: is_list_empty              |\n");
    printf("|               5: list_length         6: get_list_item              |\n");
    printf("|               7: locate_list_item    8: piror_list_item            |\n");
    printf("|               9: next_list_item     10: list_insert                |\n");
    printf("|              11: list_delete        12: print_list                 |\n");
    printf("|              0: quit                       |\n");
    printf("|                                                                    |\n");
    printf("|Enter the number of the function and see the usage and call it!     |\n");
    printf("|Enter 0 to quit the demo system.                                    |\n");
    printf("|                                                                    |\n");
    printf("+--------------------------------------------------------------------+\n");
    printf("\n");
    printf("Your choose: ");
}

int main() {
    int choose = 0xff;
    List L =List<int>();
    while (choose != 0) {
        printMenu();
        scanf("%d", &choose);
        int id, order, elem, index;
        switch (choose) {
            case 1:
                printf("/*\n");
                printf(" * Function Name: init_list\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: List L\n");
                printf(" * Return: void\n");
                printf(" * Use: initial the linear list\n");
                printf(" */\n");
                printf("\n");
                InitList<int>(L);
                printf("\n");
                break;
            case 2:
                printf("/*\n");
                printf(" * Function Name: destroyList\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: List L\n");
                printf(" * Return: void\n");
                printf(" * Use: destroy the link list\n");
                printf(" */\n");
                printf("\n");
                DestroyList(L);
                break;
            case 3:
                printf("/*\n");
                printf(" * Function Name: ClearList\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: List L\n");
                printf(" * Return: void\n");
                printf(" * Use: let the link list empty\n");
                printf(" */\n");
                printf("\n");
                ClearList(L);
                break;
            case 4:
                printf("/*\n");
                printf(" * Function Name: ListEmpty\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: List L\n");
                printf(" * Return: bool(true or false)\n");
                printf(" * Use: judge if the link list is empty\n");
                printf(" */\n");
                printf("\n");
                if (ListEmpty(L)) {
                    printf("Linear list is empty!\n");
                } else {
                    printf("Linear list is not empty!\n");
                }
                break;
            case 5:
                printf("/*\n");
                printf(" * Function Name: list_length\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: linear_list L\n");
                printf(" * Return: int(the length)\n");
                printf(" * Use: get the length of linear list\n");
                printf(" */\n");
                printf("\n");
                printf("The length of linear list is %d.\n", ListLength(L));
                break;
            case 6:
                printf("/*\n");
                printf(" * Function Name: get_list_item\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: List L, int order, int *elem\n");
                printf(" * Return: void\n");
                printf(" * Use: get the ordered element of link list\n");
                printf(" */\n");
                printf("\n");
                printf("Then, enter the list id and index: ");
                scanf("%d", &order);
                GetElem(L, order, elem);
                printf("The element is %d.\n", elem);
                break;
            case 7:
                printf("/*\n");
                printf(" * Function Name: locate_list_item\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: linear_list L, int ordered_elem\n");
                printf(" * Return: int(index)\n");
                printf(" * Use: get the index of ordered item\n");
                printf(" */\n");
                printf("\n");
                scanf("%d", &index);
                order=LocateElem<int>(L, index, [](const int &a, const int &b) { return a == b; });
                printf("The index  is %d.\n", order);
                break;
            case 8:
                printf("/*\n");
                printf(" * Function Name: piror_list_item\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: linear_list L, int elem, int *elem_pre\n");
                printf(" * Return: int(status)\n");
                printf(" * Use: get the ordered element's piror\n");
                printf(" */\n");
                printf("\n");
                scanf("%d", &elem);
                int elem_pre;
                PriorElem(L, elem, elem_pre);
                printf("The piror element of %d is %d.\n", elem, elem_pre);
                break;
            case 9:
                printf("/*\n");
                printf(" * Function Name: next_list_item\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: linear_list L, int elem, int *elem_next\n");
                printf(" * Return: int(status)\n");
                printf(" * Use: get the ordered element's next\n");
                printf(" */\n");
                printf("\n");
                scanf("%d", &elem);
                int elem_after;
                NextElem(L, elem, elem_after);
                printf("The piror element of %d is %d.\n", elem, elem_after);
                break;
            case 10:
                printf("/*\n");
                printf(" * Function Name: list_insert\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: linear_list *L, int order, int elem\n");
                printf(" * Return: int(status)\n");
                printf(" * Use: insert a element in the link list\n");
                printf(" */\n");
                printf("\n");
                printf("Then, enter the list index and element: ");
                scanf("%d %d", &order, &elem);
                ListInsert(L, order, elem);
                break;
            case 11:
                printf("/*\n");
                printf(" * Function Name: list_delete\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: linear_list *L, int order, int *elem\n");
                printf(" * Return: int(status)\n");
                printf(" * Use: delete a element in the link list\n");
                printf(" */\n");
                printf("\n");
                printf("Then, enter the list index: ");
                scanf("%d", &order);
                ListDelete(L, order, elem);
                printf("Delete %d succeed!\n", elem);
                break;
            case 12:
                printf("/*\n");
                printf(" * Function Name: print_list\n");
                printf(" * Module: Data structures\n");
                printf(" * Parameter: linear_list L, char *payload\n");
                printf(" * Return: None\n");
                printf(" * Use: print the elements of the linklist to the payload\n");
                printf(" */\n");
                printf("\n");
                ListTraverse<int>(L, [](const int &a) {
                    printf("%d", a);
                });
                printf("\n");
        }
    }
}

template<typename T>
auto InitList(List<T> &list)->void {
    list = List<T>();
}

template<typename T>
auto DestroyList(List<T> &list) ->void{
    InitList(list);
};

template<typename T>
auto ClearList(List<T> &list)->void {
    list.clear();
};

template<typename T>
auto ListEmpty(List<T> &list)-> bool {
    return list.empty();
};

template<typename T>
auto ListLength(List<T> &list) ->size_t {
    return list.length();
};

template<typename T>
auto GetElem(List<T> &list, std::size_t index, T &e) ->void{
    e = list.get(index);
    return;
};

template<typename T>
auto LocateElem(List<T> &list, const T &e, std::function<bool(const T &, const T &)> &&eq)->int {
    return list.locate(e,std::move(eq));
};

template<typename T>
auto PriorElem(List<T> &list, const T &cur_e, T &pre_e)->void {
    pre_e = list.prior(cur_e);
};

template<typename T>
auto NextElem(List<T> &list, const T &cur_e, T &next_e) ->void{
    next_e = list.next(cur_e);
};

template<typename T>
auto ListInsert(List<T> &list, std::size_t index, T &e) ->void{
    list.insert(index, e);
};

template<typename T>
auto ListDelete(List<T> &list, std::size_t index, T &e) ->void{
    e = list.remove(index);
};

template<typename T>
auto ListTraverse(List<T> &list, std::function<void(T &)> &&visit) ->void {
    list.traverse(std::move(visit));
};