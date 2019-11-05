//
// Created by john on 10/29/19.
//

#ifndef LAB3_BITREE_H
#define LAB3_BITREE_H

#include <memory>
#include <functional>

using key=int;
using pos=bool;

template<typename T>
class TreeHead;

template<typename T>
class TreeNode {
private:
    TreeNode(key);

    TreeNode(key, T val);

    T _val;

    key _index;

    std::unique_ptr<TreeNode> _leftNode;

    std::unique_ptr<TreeNode> *_rightNode;


public:
    [[nodiscard]]inline const T &val() const { return _val; }

    friend class TreeHead<T>;
};

template<typename T>
class TreeHead {
private:
    std::unique_ptr<TreeNode<T>> _root;

    TreeNode<T> *_getSibling(key);

    TreeNode <T> * _locate(key);


public:
    TreeHead();

    TreeHead(std::string, std::string);

    void clear();

    bool empty();

    int depth();

    const T &locate(key);

    void assign(key, T);

    const T &getSibling(key);

    void insert(key, pos, T);

    std::unique_ptr<T> deleteNode(key);

    void preOrderTraverse(std::function<void(const T &)> &&);

    void inOrderTraverse(std::function<void(const T &)> &&);

    void postOrderTraverse(std::function<void(const T &)> &&);

    void levelOrderTraverse(std::function<void(const T &)> &&);

    void save(std::string &&);

    void load(std::string &&);
};

#endif //LAB3_BITREE_H
