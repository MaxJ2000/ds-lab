
#ifndef SEQLIST_H
#define SEQLIST_H

#include <functional>
#include <initializer_list>
#include <memory>
#include <string>

template<typename T>
class List {
private:
    std::size_t _length;
    std::size_t _size;
    std::unique_ptr<T[]> _elem;

public:
    List();

    explicit List(std::size_t);

    T *begin() const { return _length > 0 ? &_elem[0] : nullptr; }

    T *end() const { return _length > 0 ? &_elem[_length] : nullptr; }

    [[nodiscard]] std::size_t size() const { return _size; }

    [[nodiscard]] std::size_t length() const { return _length; }

    void clear() {
        _elem.reset(new T[0]);
        _length = 0;
    }

    bool empty();

    T &operator[](std::size_t);

    T &get(std::size_t);

    std::size_t locate(T, std::function<bool(const T &, const T &)> &&);

    T &prior(const T &);

    T &next(const T &);

    void traverse(std::function<void(T &)> &&);

    void insert(const T &);

    void insert(std::size_t, const T &);

    T remove(std::size_t);

    void resize(std::size_t);

    void save(std::string &&);

    void load(std::string &&);

    template<typename S>
    friend std::ostream &operator<<(std::ostream &, const List<S> &);

    template<typename S>
    friend std::istream &operator>>(std::istream &, List<S> &);

};

#endif // SEQLIST_H