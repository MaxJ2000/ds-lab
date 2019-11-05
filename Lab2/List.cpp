//
// Created by john on 10/27/19.
//

#include "List.h"
#include <fstream>

template<typename T>
ListNode<T>::ListNode(T val):_val(val), _next(nullptr) {};

template<typename T>
ListHead<T>::ListHead():_length(0), _next(nullptr) {};

template<typename T>
ListNode<T> *ListHead<T>::_get(std::size_t index) {
    if (_length == 0 || index > _length) {
        throw std::overflow_error("get index: " + std::to_string(index));
    }
    auto tmp = _next.get();
    for (std::size_t i = 1; i <= index; i++) {
        tmp = tmp->_next.get();
    }
    return tmp;
}

template<typename T>
void ListHead<T>::clear() {
    _length = 0;
    _next.reset(nullptr);
}

template<typename T>
const T &ListHead<T>::get(std::size_t index) {
    return _get(index)->val();
}

template<typename T>
T &ListHead<T>::operator[](std::size_t index) {
    return get(index);
}

template<typename T>
std::size_t ListHead<T>::locate(const T e, std::function<bool(const T &, const T &)> &&eq) {
    auto tmp = _get(0);
    if (eq(e, tmp->val())) {
        return 0;
    }
    for (std::size_t i = 1; i < _length; i++) {
        tmp = tmp->_next.get();
        if (eq(e, tmp->val())) {
            return i;
        }
    }
    return 0;
}

template<typename T>
const T &ListHead<T>::prior(const T &e) {
//    std::size_t pos = locate(e, [](const T &a, const T &b) { return a == b; });
//    if (pos <= 0) {
//        throw std::overflow_error("get index: " + std::to_string(pos));
//    }
//    return get(pos - 1);
    auto tmp1 = _next.get();
    auto tmp2 = tmp1;
    for (std::size_t i = 1; i < length(); i++) {
        tmp2 = tmp1;
        tmp1 = tmp1->_next.get();
        if (tmp1->val() == e) {
            return tmp2->val();
        }
    }
    throw std::runtime_error("failed to find prior");
}

template<typename T>
const T &ListHead<T>::next(const T &e) {
//    std::size_t pos = locate(e, [](const T &a, const T &b) { return a == b; });
//    if (pos == _length) {
//        throw std::overflow_error("get index: " + std::to_string(pos));
//    }
//    return get(pos + 1);
    auto tmp1 = _next.get();
    auto tmp2 = tmp1;
    for (std::size_t i = 1; i < length(); i++) {
        tmp2 = tmp1;
        tmp1 = tmp1->_next.get();
        if (tmp2->val() == e) {
            return tmp1->val();
        }
    }
    throw std::runtime_error("failed to find next");
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
        auto curNode = _get(pos - 1);
        if (curNode->_next == nullptr) {
            curNode->_next = std::make_unique<ListNode<T>>(e);
        } else {
            auto tmp = std::make_unique<ListNode<T>>(e);
            tmp.get()->_next = std::move(curNode->_next);
            curNode->_next = std::move(tmp);
        }
    } else {
        if (_next == nullptr) {
            _next = std::make_unique<ListNode<T>>(e);
        } else {
            auto tmp = std::make_unique<ListNode<T>>(e);
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
    T out;
    if (pos == 0) {
        out = get(0);
        if (_length == 1) {
            _next.reset(nullptr);
        } else {
            _next = std::move(_next.get()->_next);
        }
    } else {
        auto curNode = _get(pos - 1);
        out = curNode->_next.get()->val();
        if (_length == pos + 1) {
            curNode->_next.reset(nullptr);
        } else {
            curNode->_next = std::move(curNode->_next.get()->_next);
        }
    }
    _length--;
    return out;
}

template<typename T>
Iterator<T> ListHead<T>::begin() {
    return Iterator<T>(_next.get());
}

template<typename T>
Iterator<T> ListHead<T>::end() {
    return Iterator<T>(nullptr);
}

template<typename T>
Iterator<T>::Iterator():_curNode(nullptr) {};

template<typename T>
Iterator<T>::Iterator(ListNode<T> *ptr):_curNode(ptr) {};

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T> &iterator) {
    return _curNode != iterator._curNode;
}

template<typename T>
T &Iterator<T>::operator*() {
    return _curNode->_val;
}

template<typename T>
Iterator<T> &Iterator<T>::operator++() {
    if (_curNode != nullptr) {
        _curNode = _curNode->_next.get();
    }
    return *this;
}

template<typename T>
Iterator<T> &Iterator<T>::operator++(int) {
    auto iterator = *this;
    ++*this;
    return *this;
}

template<typename T>
Iterator<T> &Iterator<T>::operator=(ListNode<T> *pNode) {
    this->_curNode = pNode;
    return *this;
}

template<typename T>
void ListHead<T>::save(std::string &&f) {
    std::ofstream fs;
    fs.open(f);
    fs << _length << std::endl;
    for (auto &&i:*this) {
        fs << i << std::endl;
    }
    fs.close();
}

template<typename T>
void ListHead<T>::load(std::string &&f) {
    std::ifstream fs;
    fs.open(f);
    T buf;
    size_t tmp;
    fs >> tmp;
    while (fs >> buf) {
        insert(buf);
    }
    fs.close();
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const ListHead<T> &list) {
    os << "List Length:" << list.length() << std::endl;
    for (auto &&i:list) {
        os << i << std::endl;
    }
    return os;
}

template<typename T>
std::istream &operator>>(std::istream &in, ListHead<T> &list) {
    T buf;
    in >> buf;
    list.insert(buf);
    return in;
}