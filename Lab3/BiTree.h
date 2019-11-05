//
// Created by john on 10/29/19.
//

#ifndef LAB3_BITREE_H
#define LAB3_BITREE_H

#include <memory>
#include <functional>

using key=unsigned long;
using pos=bool;

template<typename T>
class TreeHead;

template<typename T>
class TreeNode {
private:
    T _val;

    key _index;

    std::unique_ptr<TreeNode> _leftNode;

    std::unique_ptr<TreeNode> _rightNode;
public:
    TreeNode();

    TreeNode(T);

    TreeNode(T, key);

    [[nodiscard]]inline const T &val() const { return _val; }

    friend class TreeHead<T>;
};

template<typename T>
class TreeHead {
private:
    std::unique_ptr<TreeNode<T>> _root;

    TreeNode<T> *_locate(const key &);

    std::unique_ptr<TreeNode<T>> _createTree(std::string &&, std::string &&);

    void _markIndex(TreeNode<T> *);

public:
    TreeHead();

    TreeHead(std::string &&, std::string &&);

    void clear() {
        _root.reset();
    };

    inline bool empty() {
        return _root == nullptr;
    };

    unsigned long depth();

    unsigned long depth(TreeNode<T> *);

    const T &locate(key);

    void assign(const key &, const T &);

    const T &getSibling(const key &);

    void insert(const key &, const pos &, const T &);

    std::unique_ptr<T> deleteNode(const key &);

    void preOrderTraverse(std::function<void(const T &)> &&);

    void inOrderTraverse(std::function<void(const T &)> &&);

    void postOrderTraverse(std::function<void(const T &)> &&);

    void levelOrderTraverse(std::function<void(const T &)> &&);

    void save(std::string &&);

    void load(std::string &&);
};

#endif //LAB3_BITREE_H
