//
// Created by john on 10/27/19.
//

#include "List.h"
#include <fstream>

template<typename T>
ListNode<T>::ListNode(T val):_ptr(nullptr), _val(val) {};

template<typename T>
ListHead<T>::ListHead():_length(0), _ptr(nullptr) {};

template<typename T>
ListNode<T> *ListHead<T>::_get(size_t index) {
    T *tmp = nullptr;
    if (_length == 0 || index > _length) {
        throw std::overflow_error("get index: " + std::to_string(index));
    }
    for (size_t i = 0; i < index; i++) {
        tmp = ptr().get();
    }
    return tmp;
}

template<typename T>
void ListHead<T>::clear() {
    _length = 0;
    _ptr.reset(nullptr);
}

template<typename T>
T &ListHead<T>::get(size_t index) {
    return _get(index)->val();
}

template<typename T>
T &ListHead<T>::operator[](size_t index) {
    return get(index);
}

template<typename T>
size_t ListHead<T>::locate(T, std::function<bool(const T &, const T &)> &&) {
    
}