//
// Created by john on 10/29/19.
//

#include "BiTree.h"

template<typename T>
TreeNode<T>::TreeNode() {};

template<typename T>
TreeNode<T>::TreeNode(T val):_val(val) {};

template<typename T>
TreeNode<T>::TreeNode(T val, key index):_index(index), _val(val) {};

template<typename T>
TreeHead<T>::TreeHead():_root(nullptr) {};

template<typename T>
TreeHead<T>::TreeHead(std::string &&preOrderDef, std::string &&inOrderDef) {
    auto len = preOrderDef.length();
    if (len != inOrderDef.length()) {
        throw std::logic_error(
                "Defination length:" +
                std::to_string(len)
                + "and" +
                std::to_string(inOrderDef.length()));
    }
    _root = _createTree(std::move(preOrderDef), std::move(inOrderDef));
    _markIndex(_root.get());
}

template<typename T>
std::unique_ptr<TreeNode<T>>
TreeHead<T>::_createTree(std::string &&preOrderDef, std::string &&inOrderDef) {
    auto len = preOrderDef.length();
    auto ptr = std::make_unique<TreeNode<T>>();
    for (unsigned i = 0; i < len; ++i) {
        if (preOrderDef[0] == inOrderDef[i]) {
            ptr.get()->_val = preOrderDef[0];
            if (i != 0) {
                ptr.get()->_leftNode = _createTree(preOrderDef.substr(1, i), inOrderDef.substr(0, i));
            }
            if (len - i - 1 != 0) {
                ptr.get()->_rightNode = _createTree(preOrderDef.substr(i + 1, len - i - 1),
                                                    inOrderDef.substr(i + 1, len - i - 1));
            }
        }
    }
    return ptr;
}

template<typename T>
void TreeHead<T>::_markIndex(TreeNode<T> *node) {
    auto fIndex = node->_index;
    auto leftNode = node->_leftNode.get();
    auto rightNode = node->_rightNode.get();
    if (leftNode != nullptr) {
        leftNode->_index = fIndex * 2 + 1;
        _markIndex(leftNode);
    }
    if (rightNode != nullptr) {
        rightNode->_index = fIndex * 2 + 2;
        _markIndex(rightNode);
    }
}

template<typename T>
unsigned long TreeHead<T>::depth() {
    return depth(_root.get());
}

template<typename T>
unsigned long TreeHead<T>::depth(TreeNode<T> *node) {
    auto leftNode = node->_leftNode.get();
    auto rightNode = node->_rightNode.get();
    unsigned long lDepth = 1;
    unsigned long rDepth = 1;
    if (leftNode != nullptr) {
        lDepth = depth(leftNode) + 1;
    }
    if (rightNode != nullptr) {
        rDepth = depth(rightNode) + 1;
    }
    return lDepth > rDepth ? lDepth : rDepth;
}

template<typename T>
const T &TreeHead<T>::locate(key index) {
    std::vector<bool> rWay;
    auto node = _root.get();
    while (index != 0) {
        bool tmp = index % 2;
        rWay.push_back(tmp);
        index = (index - 1) / 2;
    }
    for (auto rIterator = rWay.rbegin(); rIterator != rWay.rend(); rIterator++) {
        if (*rIterator) {
            node = node->_leftNode.get();
        } else {
            node = node->_rightNode.get();
        }
    }
    return node->val();
}