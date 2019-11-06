//
// Created by john on 11/6/19.
//

#ifndef LAB3_STACK_H
#define LAB3_STACK_H

#include <memory>

template<typename T>
class stack {
private:
    std::unique_ptr<T[]> _arr;
    std::size_t _top;
    std::size_t _capacity;
public:
    stack(std::size_t);

    void push(T);

    T pop();

    inline std::size_t size() { return _top + 1; };

    inline bool empty() { return _top == -1 };

    inline bool full() { return _top == _capacity - 1; };
};

template<typename T>
stack<T>::stack(std::size_t size):_capacity(size), _arr(std::make_unique<T[]>(size), _top(-1)) {};

template<typename T>
void stack<T>::push(T x) {
    if (full()) {
        throw std::overflow_error("full!");
    }
    _arr[++_top] = x;
}

template<typename T>
T stack<T>::pop() {
    if(empty()){
        throw std::underflow_error("empty!");
    }
    return _arr[_top--];
}
#endif //LAB3_STACK_H
