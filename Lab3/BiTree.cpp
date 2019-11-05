//
// Created by john on 10/29/19.
//

#include "BiTree.h"

template<typename T>
TreeNode<T>::TreeNode(key index):_index(index) {};


template<typename T>
TreeNode<T>::TreeNode(key index, T val):_index(index), _val(val) {};

template<typename T>
TreeHead<T>::TreeHead():_root(std::make_unique<TreeNode<T>>(0)) {};

template<typename T>
TreeHead<T>::TreeHead(std::string preOrderDef, std::string inOrderDef) {

}