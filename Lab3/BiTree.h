//
// Created by john on 10/29/19.
//

#ifndef LAB3_BITREE_H
#define LAB3_BITREE_H

#include <memory>

template<typename T>
class TreeHead;

template<typename T>
class TreeNode {
private:
    T _val;

    std::unique_ptr<TreeNode> _leftNode;

    std::unique_ptr<TreeNode> *_rightNode;

    TreeNode();

    TreeNode(T val);

public:
    [[nodiscard]]inline const T &val() const { return _val; }

    friend class TreeHead<T>;
};

template<typename T>
class TreeHead {
private:
    std::unique_ptr<TreeNode<T>> _root;
public:
    TreeHead();

    TreeHead(std::string, std::string);

    void clear();

    bool empty();

    int depth();

    const T &locate(T);
};

#endif //LAB3_BITREE_H
