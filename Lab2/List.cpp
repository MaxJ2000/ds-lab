//
// Created by john on 10/27/19.
//

#include "List.h"
#include <fstream>

template<typename T>
ListNode<T>::ListNode(T val):_next(nullptr), _val(val) {};

template<typename T>
ListHead<T>::ListHead():_length(0), _next(nullptr) {};

template<typename T>
ListNode<T> *ListHead<T>::_get(std::size_t index) {
    ListNode<T> *tmp = nullptr;
    if (_length == 0 || index > _length) {
        throw std::overflow_error("get index: " + std::to_string(index));
    }
    for (std::size_t i = 0; i <= index; i++) {
        tmp = _next.get();
    }
    return tmp;
}

template<typename T>
void ListHead<T>::clear() {
    _length = 0;
    _next.reset(nullptr);
}

template<typename T>
T &ListHead<T>::get(std::size_t index) {
    return _get(index)->val();
}

template<typename T>
T &ListHead<T>::operator[](std::size_t index) {
    return get(index);
}

template<typename T>
std::size_t ListHead<T>::locate(const T e, std::function<bool(const T &, const T &)> &&eq) {
    for (std::size_t i = 0; i < _length; i++) {
        if (eq(e, get(i))) {
            return i;
        }
    }
    return 0;
}

template<typename T>
T &ListHead<T>::prior(const T &e) {
    std::size_t pos = locate(e, [](const T &a, const T &b) { return a == b; });
    if (pos <= 0) {
        throw std::overflow_error("get index: " + std::to_string(pos));
    }
    return get(pos - 1);
}

template<typename T>
T &ListHead<T>::next(const T &e) {
    std::size_t pos = locate(e, [](const T &a, const T &b) { return a == b; });
    if (pos == _length) {
        throw std::overflow_error("get index: " + std::to_string(pos));
    }
    return get(pos + 1);
}

template<typename T>
void ListHead<T>::traverse(std::function<void(T &)> &&f) {
    for (auto &&i:*this) {
        f(i);
    }
}

template<typename T>
void ListHead<T>::insert(std::size_t pos, const T &e) {
    if (pos < 0 || pos > _length) {
        throw std::overflow_error("get pos: " + std::to_string(pos));
    }
    if (pos != 0) {
        ListNode<T> *curNode = _get(pos - 1);
        if (curNode->_next == nullptr) {
            curNode->_next = std::make_unique<ListNode<T>>(e);
        } else {
            std::unique_ptr<ListNode<T>> tmp = std::make_unique<ListNode<T>>(e);
            tmp.get()->_next = std::move(curNode->_next);
            curNode->_next = std::move(tmp);
        }
    } else {
        if (_next == nullptr) {
            _next = std::make_unique<ListNode<T>>(e);
        } else {
            std::unique_ptr<ListNode<T>> tmp = std::make_unique<ListNode<T>>(e);
            tmp.get()->_next = std::move(_next);
            _next = std::move(tmp);
        }
    }
    _length++;
}

template<typename T>
void ListHead<T>::insert(const T &e) {
    insert(length(), e);
}

template<typename T>
T ListHead<T>::remove(std::size_t pos) {
    if (pos < 0 || _length <= pos) {
        throw std::overflow_error("get index: " + std::to_string(pos));
    }
    T out = get(pos);
    if (pos == 0) {
        if (_length == 1) {
            _next.reset(nullptr);
        } else {
            _next = std::move(_next.get()->_next);
        }
    } else {
        ListNode<T> *curNode = _get(pos - 1);
        if (_length == pos + 1) {
            curNode->_next.reset(nullptr);
        } else {
            curNode->_next = std::move(curNode->_next.get()->_next);
        }
    }
    _length--;
}

template<typename T>
typename ListHead<T>::Iterator ListHead<T>::begin() {
    return Iterator(_next.get());
}

template<typename T>
typename ListHead<T>::Iterator ListHead<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
ListHead<T>::Iterator::Iterator():_curNode(nullptr) {};

template<typename T>
ListHead<T>::Iterator::Iterator(const ListNode<T> *ptr):_curNode(ptr) {};

template<typename T>
bool ListHead<T>::Iterator::operator!=(const ListHead<T>::Iterator &iterator) {
    return _curNode != iterator._curNode;
}

template<typename T>
T ListHead<T>::Iterator::operator*() {
    return _curNode->val();
}

template<typename T>
typename ListHead<T>::Iterator &ListHead<T>::Iterator::operator++() {
    if (_curNode != nullptr) {
        _curNode = _curNode->_next.get();
    }
    return *this;
}

template<typename T>
typename ListHead<T>::Iterator &ListHead<T>::Iterator::operator++(int) {
    Iterator iterator = *this;
    ++*this;
    return *this;
}

template<typename T>
typename ListHead<T>::Iterator &ListHead<T>::Iterator::operator=(ListNode<T> *pNode) {
    this->_curNode = pNode;
    return *this;
}