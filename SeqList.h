
#ifndef SEQLIST_H
#define SEQLIST_H

#include <bits/c++config.h>
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

    [[nodiscard]] inline auto begin() const -> T * { return _length > 0 ? &_elem[0] : nullptr; }

    [[nodiscard]] inline auto end() const -> T * { return _length > 0 ? &_elem[_length] : nullptr; }

    [[nodiscard]] inline auto size() const { return _size; }

    [[nodiscard]] inline auto length() const { return _length; }

    auto empty() -> bool;

    auto operator[](std::size_t) -> T &;

    auto get(std::size_t) -> T &;

    auto locate(T, std::function<bool(const T &, const T &)> &&) -> std::size_t;

    auto prior(const T &) -> T &;

    auto next(const T &) -> T &;

    auto traverse(std::function<void(T &)> &&) -> void;

    auto resize(std::size_t) -> void;

    auto insert(std::size_t, const T &) -> void;

    auto remove(std::size_t, T &) -> void;

    auto remove(std::size_t) -> T;

};

#endif // SEQLIST_H