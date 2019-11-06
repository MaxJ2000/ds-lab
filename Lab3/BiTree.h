//
// Created by john on 10/29/19.
//

#ifndef LAB3_BITREE_H
#define LAB3_BITREE_H

#include <memory>
#include <functional>
#include <vector>

using nodeIndex=unsigned long;
using nodeKey=std::string;

template<typename T>
class TreeHead;

template<typename T>
class TreeNode {
private:
    T _val;

    nodeIndex _index{};

    nodeKey _key;

    std::unique_ptr<TreeNode> _leftNode;

    std::unique_ptr<TreeNode> _rightNode;
public:
    TreeNode(nodeKey);

    TreeNode(nodeKey, T);

    TreeNode(nodeKey, T, nodeIndex);

    [[nodiscard]]inline const T &val() const { return _val; }

    friend class TreeHead<T>;
};

template<typename T>
class TreeHead {
private:
    std::unique_ptr<TreeNode<T>> _root;

    TreeNode<T> *_locateByIndex(const nodeIndex &);

    TreeNode<T> *_locateByKey(const nodeKey &);

    TreeNode<T> *_locateFatherByKey(const nodeKey &);

    void _markIndex(TreeNode<T> *);

public:
    TreeHead();

    TreeHead(std::vector<nodeKey>, std::vector<nodeKey>);

    void clear() {
        _root.reset();
    };

    inline bool empty() {
        return _root == nullptr;
    };

    unsigned long depth();

    unsigned long depth(TreeNode<T> *);

    void assign(const nodeKey &, const T &);

    TreeNode<T> *getSibling(const nodeKey &);

    void insert(const nodeKey &, const bool &, std::unique_ptr<TreeNode<T>>);

    std::unique_ptr<TreeNode<T>> deleteNode(const nodeKey &);

    void preOrderTraverse(std::function<void(const nodeKey &, const T &)> &&);

    void inOrderTraverse(std::function<void(const nodeKey &, const T &)> &&);

    void postOrderTraverse(std::function<void(const nodeKey &, const T &)> &&);

    void levelOrderTraverse(std::function<void(const nodeKey &, const T &)> &&);

    void save(std::string &&);

    void load(std::string &&);
};

#endif //LAB3_BITREE_H
