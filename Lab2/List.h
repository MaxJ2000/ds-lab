//
// Created by john on 10/27/19.
//

#ifndef LAB2_LIST_H
#define LAB2_LIST_H

#include <functional>
#include <initializer_list>
#include <memory>
#include <string>

template<typename T>
class ListNode {
private:
    T _val;
    std::unique_ptr<ListNode<T>> _ptr;
public:
    explicit ListNode(T val);

    T inline val() { return _val; }

    std::unique_ptr<ListNode<T>> inline ptr() { return _ptr; }
};

template<typename T>
class ListHead {
private:
    std::size_t _length;
    std::unique_ptr<ListNode<T>> _ptr;

    ListNode<T> *_get(size_t);

public:
    ListHead();

    bool inline empty() { return _length == 0; };

    std::unique_ptr<ListNode<T>> inline ptr() { return _ptr; };

    [[nodiscard]] size_t length() const { return _length; }

    void clear();

    T &operator[](size_t);

    T &get(std::size_t);

    size_t locate(T, std::function<bool(const T &, const T &)> &&);

    T &prior(const T &);

    T &next(const T &);

    void traverse(std::function<void(T &)> &&);

    void insert(const T &);

    void insert(std::size_t, const T &);

    T remove(std::size_t);

    void save(std::string &&);

    void load(std::string &&);

    template<typename S>
    friend std::ostream &operator<<(std::ostream &, const ListHead<S> &);

    template<typename S>
    friend std::istream &operator>>(std::istream &, ListHead<S> &);
};


#endif //LAB2_LIST_H
