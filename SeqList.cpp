#include "SeqList.h"

template<typename T>
List<T>::List() : _length(0), _size(0), _elem(std::make_unique<T[]>(0)) {}

template<typename T>
List<T>::List(std::size_t size)
        : _length(0), _size(size), _elem(std::make_unique<T[]>(size)) {
    // see:
    // https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array
}

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
    auto pos = locate(e, [](const std::string &a, const std::string &b) { return a == b; });
    if (pos <= 0) {
        throw std::overflow_error("get index: " + std::to_string(pos));
    }
    return _elem[pos - 1];
}

template<typename T>
auto List<T>::next(const T &e) -> T & {
    auto pos = locate(e, [](const std::string &a, const std::string &b) { return a == b; });
    if (pos == _length) {
        throw std::overflow_error("get index: " + std::to_string(pos));
    }
    return _elem[pos + 1];
}


template<typename T>
auto List<T>::traverse(std::function<void(T &)> &&f) {
    for (auto &&i : *this) {
        f(i);
    }
}


template<typename T>
auto List<T>::resize(std::size_t size){
    if (size < _size) {
        throw std::overflow_error("get index: " + std::to_string(size));
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
auto List<T>::insert(std::size_t pos, const T &e) {
    if (pos > _size + 1 || pos < 1) {
        // TODO(error): throw error
        return;
    }

    if (_length == _size) {
        resize(_size * 2);
    }
    auto data = _elem.get();
    for (std::size_t i = _length; i >= pos; i--) {
        data[i] = data[i - 1];
    }
    _length++;
    data[pos - 1] = e;
}

template<typename T>
auto List<T>::remove(std::size_t index) -> T {
    if (index < 1 || _length < index) {
        // TODO(error): throw error
    }
    auto out = _elem[index - 1];

    auto data = _elem.get();
    for (std::size_t i = index - 1; i < _length; i++) {
        data[i] = data[i + 1];
    }
    _length--;
    return out;
}

template<typename T>
auto List<T>::remove(std::size_t index, T &out) {
    if (index < 1 || _length < index) {
        // TODO(error): throw error
    }
    out = _elem[index - 1];

    auto data = _elem.get();
    for (std::size_t i = index - 1; i < _length; i++) {
        data[i] = data[i + 1];
    }
    _length--;
}
