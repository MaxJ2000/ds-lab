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
class ListHead;

template<typename T>
class Iterator;

template<typename T>
class ListNode {
private:
    T _val;

    std::unique_ptr<ListNode> _next;

public:
    explicit ListNode(T val);

    [[nodiscard]]inline const T &val() const { return _val; }

    friend class ListHead<T>;

    friend class Iterator<T>;

};

template<typename T>
class Iterator {
private:
    ListNode<T> *_curNode;
public:
    explicit Iterator();

    explicit Iterator(ListNode<T> *);

    Iterator &operator=(ListNode<T> *);

    Iterator &operator++();

    Iterator &operator++(int);

    bool operator!=(const Iterator &);

    T &operator*();


};


template<typename T>
class ListHead {

private:
    std::size_t _length;

    std::unique_ptr<ListNode<T>> _next;

    ListNode<T> *_get(size_t);

public:
    ListHead();

    bool inline empty() { return _length == 0; };

    [[nodiscard]] size_t inline length() const { return _length; }

    void clear();

    T &operator[](size_t);

    const T &get(std::size_t);

    size_t locate(T, std::function<bool(const T &, const T &)> &&);

    const T &prior(const T &);

    const T &next(const T &);

    void traverse(std::function<void(T &)> &&);

    void insert(std::size_t, const T &);

    void insert(const T &);

    T remove(std::size_t);

    void save(std::string &&);

    void load(std::string &&);

    Iterator<T> begin();

    Iterator<T> end();

    template<typename S>
    friend std::ostream &operator<<(std::ostream &, const ListHead<S> &);

    template<typename S>
    friend std::istream &operator>>(std::istream &, ListHead<S> &);

};

#endif //LAB2_LIST_H
