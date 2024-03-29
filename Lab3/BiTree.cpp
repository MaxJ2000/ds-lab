//
// Created by john on 10/29/19.
//
#include <utility>
#include <queue>
#include <fstream>

#include "BiTree.h"
#include "stack.h"



template<typename T>
TreeNode<T>::TreeNode(nodeKey key):_key(std::move(key)){}

template<typename T>
TreeNode<T>::TreeNode(nodeKey key, T val):_key(std::move(key)), _val(val){}

template<typename T>
TreeHead<T>::TreeHead():_root() {}

template<typename T>
TreeHead<T>::TreeHead(std::vector<nodeKey> preOrderDef, std::vector<nodeKey> inOrderDef, std::vector<T> value) {
    auto n = preOrderDef.size();
    std::function<std::unique_ptr<TreeNode<T>>(std::size_t, std::size_t, std::size_t)> createTree;
    createTree = [&preOrderDef, &inOrderDef, &value, &createTree](
            auto pos1, auto pos2, auto n) {
        auto ptr = std::make_unique<TreeNode<T>>(preOrderDef[pos1], value[pos1]);
        for (unsigned long i = 0; i < n; ++i) {
            if (preOrderDef[pos1] == inOrderDef[pos2 + i]) {
                if (i != 0) {
                    ptr.get()->_leftNode = createTree(pos1 + 1, pos2, i);
                }
                if (n - i - 1 != 0) {
                    ptr.get()->_rightNode = createTree(pos1 + i + 1, pos2 + i + 1, n - i - 1);
                }
            }
        }
        return ptr;
    };
    if (n != inOrderDef.size()) {
        throw std::logic_error(
                "Definition length:" +
                std::to_string(n)
                + "and" +
                std::to_string(inOrderDef.size()));
    }
    _root = createTree(0, 0, n);
}

template<typename T>
unsigned long TreeHead<T>::depth() {
//    auto a = _locateFatherByKey("F");
//    getchar();
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
TreeNode<T> *TreeHead<T>::_locateByKey(const nodeKey &key) {
    TreeNode<T> *tmp = nullptr;
    std::function<void(TreeNode<T> *)> locateFunc = [&tmp, &key, &locateFunc](TreeNode<T> *node) {
        if (node->_key == key) {
            tmp = node;
            return;
        }
        auto leftNode = node->_leftNode.get();
        auto rightNode = node->_rightNode.get();
        if (leftNode != nullptr) {
            locateFunc(leftNode);
        }
        if (rightNode != nullptr) {
            locateFunc(rightNode);
        }
    };
    locateFunc(_root.get());
    if (tmp == nullptr) {
        throw std::runtime_error("Bad key");
    }
    return tmp;
}

template<typename T>
TreeNode<T> *TreeHead<T>::_locateFatherByKey(const nodeKey &key) {
    TreeNode<T> *tmpFather = nullptr;

    std::function<void(TreeNode<T> *, TreeNode<T> *)> locateFunc = [&tmpFather, &key, &locateFunc](
            TreeNode<T> *fatherNode,
            TreeNode<T> *node) {
        if (node->_key == key) {
            tmpFather = fatherNode;
            return;
        }
        auto leftNode = node->_leftNode.get();
        auto rightNode = node->_rightNode.get();
        if (leftNode != nullptr) {
            locateFunc(node, leftNode);
        }
        if (rightNode != nullptr) {
            locateFunc(node, rightNode);
        }
    };
    locateFunc(nullptr, _root.get());
    if (tmpFather == nullptr) {
        throw std::runtime_error("Bad key");
    }
    return tmpFather;
}

template<typename T>
const T &TreeHead<T>::locate(const nodeKey &key) {
    return _locateByKey(key)->val();
}

template<typename T>
void TreeHead<T>::assign(const nodeKey &key, const T &val) {
    auto node = _locateByKey(key);
    node->_val = val;
}

template<typename T>
void TreeHead<T>::insert(const nodeKey &key, const bool &choice, std::unique_ptr<TreeNode<T>> targetNode) {
    auto node = _locateByKey(key);
    if (choice) {
        targetNode.get()->_rightNode = std::move(node->_rightNode);
        node->_rightNode = std::move(targetNode);
    } else {
        targetNode.get()->_rightNode = std::move(node->_leftNode);
        node->_leftNode = std::move(targetNode);
    }
}

template<typename T>
std::unique_ptr<TreeNode<T>> TreeHead<T>::deleteNode(const nodeKey &key) {
    std::unique_ptr<TreeNode<T>> tmpNode;
    if (_root.get()->key() != key) {
        auto fatherNode = _locateFatherByKey(key);
        auto pos = fatherNode->_rightNode.get()->key() == key ? 1 : 0;
        auto childNode = pos ?
                         fatherNode->_rightNode.get() :
                         fatherNode->_leftNode.get();
        if (childNode->_leftNode == nullptr && childNode->_rightNode == nullptr) {
            if (pos) {
                tmpNode = std::move(fatherNode->_rightNode);
            } else {
                tmpNode = std::move(fatherNode->_leftNode);
            }
        }
        if (childNode->_leftNode != nullptr && childNode->_rightNode == nullptr) {
            if (pos) {
                tmpNode = std::move(fatherNode->_rightNode);
                fatherNode->_rightNode = std::move(childNode->_leftNode);
            } else {
                tmpNode = std::move(fatherNode->_leftNode);
                fatherNode->_leftNode = std::move(childNode->_leftNode);
            }
        }
        if (childNode->_rightNode != nullptr && childNode->_leftNode == nullptr) {
            if (pos) {
                tmpNode = std::move(fatherNode->_rightNode);
                fatherNode->_rightNode = std::move(childNode->_rightNode);
            } else {
                tmpNode = std::move(fatherNode->_leftNode);
                fatherNode->_leftNode = std::move(childNode->_rightNode);
            }
        }
        if (childNode->_rightNode != nullptr && childNode->_leftNode != nullptr) {
            auto tmp = childNode->_leftNode.get();
            while (tmp->_rightNode != nullptr) {
                tmp = tmp->_rightNode.get();
            }
            tmp->_rightNode = std::move(childNode->_rightNode);
            if (pos) {
                tmpNode = std::move(fatherNode->_rightNode);
                fatherNode->_rightNode = std::move(childNode->_leftNode);
            } else {
                tmpNode = std::move(fatherNode->_leftNode);
                fatherNode->_leftNode = std::move(childNode->_leftNode);
            }
        }
    } else {
        auto childNode = _root.get();
        if (childNode->_leftNode == nullptr && childNode->_rightNode == nullptr) {
            tmpNode = std::move(_root);
        }
        if (childNode->_leftNode != nullptr && childNode->_rightNode == nullptr) {
            tmpNode = std::move(_root);
            _root = std::move(childNode->_leftNode);
        }
        if (childNode->_rightNode != nullptr && childNode->_leftNode == nullptr) {
            tmpNode = std::move(_root);
            _root = std::move(childNode->_rightNode);
        }
        if (childNode->_rightNode != nullptr && childNode->_leftNode != nullptr) {
            auto tmp = childNode->_leftNode.get();
            while (tmp->_rightNode != nullptr) {
                tmp = tmp->_rightNode.get();
            }
            tmp->_rightNode = std::move(childNode->_rightNode);
            tmpNode = std::move(_root);
            _root = std::move(childNode->_leftNode);
        }
    }
    return tmpNode;
}

template<typename T>
TreeNode<T> *TreeHead<T>::getSibling(const nodeKey &key) {
    TreeNode<T> *tmpSibling = nullptr;

    std::function<void(TreeNode<T> *, TreeNode<T> *)> locateFunc = [&key, &tmpSibling, &locateFunc](
            TreeNode<T> *fatherNode,
            TreeNode<T> *node) {
        if (node->_key == key) {
            if (fatherNode->_leftNode.get() != nullptr && fatherNode->_leftNode.get()->key() != key) {
                tmpSibling = fatherNode->_leftNode.get();
            } else {
                tmpSibling = fatherNode->_rightNode.get();
            }
            return;
        }
        auto leftNode = node->_leftNode.get();
        auto rightNode = node->_rightNode.get();
        if (leftNode != nullptr) {
            locateFunc(node, leftNode);
        }
        if (rightNode != nullptr) {
            locateFunc(node, rightNode);
        }
    };
    locateFunc(nullptr, _root.get());
    return tmpSibling;
}

template<typename T>
void TreeHead<T>::preOrderTraverse(std::function<void(const nodeKey &, const T &)> &&f) {
    std::function<void(TreeNode<T> *)> traverse = [&f, &traverse](TreeNode<T> *node) {
        f(node->_key, node->_val);
        if (node->_leftNode.get() != nullptr) {
            traverse(node->_leftNode.get());
        }
        if (node->_rightNode.get() != nullptr) {
            traverse(node->_rightNode.get());
        }
    };
    traverse(_root.get());
}

template<typename T>
void TreeHead<T>::inOrderTraverse(std::function<void(const nodeKey &, const T &)> &&f) {
    stack<TreeNode<T> *> stack(depth());
    auto curNode = _root.get();
    while (curNode != nullptr || !stack.empty()) {
        while (curNode != nullptr) {
            stack.push(curNode);
            curNode = curNode->_leftNode.get();
        }
        curNode = stack.pop();
        f(curNode->key(), curNode->val());
        curNode = curNode->_rightNode.get();
    }
}

template<typename T>
void TreeHead<T>::postOrderTraverse(std::function<void(const nodeKey &, const T &)> &&f) {
    stack<TreeNode<T> *> stack(depth());
    auto curNode = _root.get();
    TreeNode<T> *last = nullptr;
    while (curNode != nullptr || !stack.empty()) {
        while (curNode != nullptr) {
            stack.push(curNode);
            curNode = curNode->_leftNode.get();
        }
        curNode = stack.peek();
        if (curNode->_rightNode == nullptr || curNode->_rightNode.get() == last) {
            stack.pop();
            f(curNode->key(), curNode->val());
            last = curNode;
            curNode = nullptr;
        } else {
            curNode = curNode->_rightNode.get();
        }
    }
}

template<typename T>
void TreeHead<T>::levelOrderTraverse(std::function<void(const nodeKey &, const T &)> &&f) {
    std::queue<TreeNode<T> *> queue;
    TreeNode<T> *tmpNode;
    queue.push(_root.get());
    while (!queue.empty()) {
        tmpNode = queue.front();
        queue.pop();
        if (tmpNode == nullptr) {
            continue;
        }
        f(tmpNode->key(), tmpNode->val());
        if (tmpNode->_leftNode != nullptr) {
            queue.push(tmpNode->_leftNode.get());
        }
        if (tmpNode->_rightNode != nullptr) {
            queue.push(tmpNode->_rightNode.get());
        }
    }
}

template<typename T>
void TreeHead<T>::save(std::string &&file) {
    std::ofstream fs;
    auto keySaver = [&fs](const nodeKey &key, const T &val) {
        fs << key << std::endl;
    };
    auto valSaver = [&fs](const nodeKey &key, const T &val) {
        fs << val << std::endl;
    };
    fs.open(file + "preOrderDef.sav");
    preOrderTraverse(keySaver);
    fs.close();
    fs.open(file + "inOrderDef.sav");
    inOrderTraverse(keySaver);
    fs.close();
    fs.open(file + "val.sav");
    preOrderTraverse(valSaver);
    fs.close();
}

template<typename T>
void TreeHead<T>::load(std::string &&file) {
    std::ifstream fs;
    nodeKey keyBuf;
    T valBuf;
    std::vector<nodeKey> preOrderDef;
    std::vector<nodeKey> inOrderDef;
    std::vector<nodeKey> value;
    fs.open(file + "preOrderDef.sav");
    while (fs >> keyBuf) {
        preOrderDef.push_back(keyBuf);
    }
    fs.close();
    fs.open(file + "inOrderDef.sav");
    while (fs >> keyBuf) {
        inOrderDef.push_back(keyBuf);
    }
    fs.close();
    fs.open(file + "val.sav");
    while (fs >> valBuf) {
        value.push_back(valBuf);
    }
    fs.close();

    auto n = preOrderDef.size();
    std::function<std::unique_ptr<TreeNode<T>>(std::size_t, std::size_t, std::size_t)> createTree;
    createTree = [&preOrderDef, &inOrderDef, &value, &createTree](
            auto pos1, auto pos2, auto n) {
        auto ptr = std::make_unique<TreeNode<T>>(preOrderDef[pos1], value[pos1]);
        for (unsigned long i = 0; i < n; ++i) {
            if (preOrderDef[pos1] == inOrderDef[pos2 + i]) {
                if (i != 0) {
                    ptr.get()->_leftNode = createTree(pos1 + 1, pos2, i);
                }
                if (n - i - 1 != 0) {
                    ptr.get()->_rightNode = createTree(pos1 + i + 1, pos2 + i + 1, n - i - 1);
                }
            }
        }
        return ptr;
    };
    if (n != inOrderDef.size()) {
        throw std::logic_error(
                "Definition length:" +
                std::to_string(n)
                + "and" +
                std::to_string(inOrderDef.size()));
    }
    _root = createTree(0, 0, n);
}