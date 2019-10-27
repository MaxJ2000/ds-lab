#include <fstream>
#include "SeqList.h"

template<typename T>
List<T>::List() : _length(0), _size(0), _elem(std::make_unique<T[]>(0)) {}

template<typename T>
List<T>::List(std::size_t size)
        : _length(0), _size(size), _elem(std::make_unique<T[]>(size)) {}

template<typename T>
auto List<T>::operator[](std::size_t index) -> T & {
    if (index >= _size) {
        throw std::overflow_error("get index: " + std::to_string(index));
    }
    return _elem[index];
}


template<typename T>
auto List<T>::empty() -> bool {
    return _length == 0;
}


template<typename T>
auto List<T>::get(std::size_t index) -> T & {
    if (index >= _size) {
        throw std::overflow_error("get index: " + std::to_string(index));
    }
    return _elem[index];
}

template<typename T>
auto List<T>::locate(const T e, std::function<bool(const T &, const T &)> &&eq) -> std::size_t {
    for (std::size_t i = 0; i < _length; i++) {
        if (eq(e, _elem[i])) {
            return i;
        }
    }
    return 0;
}

template<typename T>
auto List<T>::prior(const T &e) -> T & {
    auto pos = locate(e, [](const T &a, const T &b) { return a == b; });
    if (pos <= 0) {
        throw std::overflow_error("get index: " + std::to_string(pos));
    }
    return _elem[pos - 1];
}

template<typename T>
auto List<T>::next(const T &e) -> T & {
    auto pos = locate(e, [](const T &a, const T &b) { return a == b; });
    if (pos == _length) {
        throw std::overflow_error("get index: " + std::to_string(pos));
    }
    return _elem[pos + 1];
}


template<typename T>
auto List<T>::traverse(std::function<void(T &)> &&f) -> void {
    for (auto &&i : *this) {
        f(i);
    }
}

template<typename T>
auto List<T>::insert(std::size_t pos, const T &e) -> void {
    if (pos > _size || pos < 0) {
        throw std::overflow_error("get pos: " + std::to_string(pos));
    }
    if (_size) {
        if (_length == _size) {
            resize(_size * 2);
        }
    } else {
        resize(1);
    }

    auto data = _elem.get();
    for (std::size_t i = _length; i > pos; i--) {
        data[i] = data[i - 1];
    }
    _length++;
    data[pos] = e;
}

template<typename T>
auto List<T>::insert(const T &e) -> void {
    insert(length(), e);
}

template<typename T>
auto List<T>::remove(std::size_t index) -> T {
    if (index < 0 || _length <= index) {
        throw std::overflow_error("get index: " + std::to_string(index));
    }
    auto out = _elem[index];

    auto data = _elem.get();
    for (std::size_t i = index; i < _length; i++) {
        data[i] = data[i + 1];
    }
    _length--;
    return out;
}


template<typename T>
auto List<T>::resize(std::size_t size) -> void {
    if (size < _size) {
        return;
    }
    auto p = std::make_unique<T[]>(size);
    auto oldElem = _elem.get();
    auto elem = p.get();
    for (std::size_t i = 0; i < _length; i++) {
        elem[i] = oldElem[i];
    }
    _elem.swap(p);
    _size = size;
}

template<typename T>
auto List<T>::save(std::string &&f) -> void {
    std::ofstream fs;
    fs.open(f);
    fs << _size << std::endl;
    for (auto &&i:*this) {
        fs << i << std::endl;
    }
    fs.close();
}

template<typename T>
auto List<T>::load(std::string &&f) -> void {
    std::ifstream fs;
    fs.open(f);
    T buf;
    size_t tmp;
    fs >> tmp;
    resize(tmp);
    while (fs >> buf) {
        insert(buf);
    }
    fs.close();
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &list) {
    os << "List Length:" << list.length() << std::endl;
    for (auto &&i:list) {
        os << i << std::endl;
    }
    return os;
}

template<typename T>
std::istream &operator>>(std::istream &in, List<T> &list) {
    T buf;
    in >> buf;
    list.insert(buf);
    return in;
}
