//
// Created by john on 11/25/19.
//

#include "graph.h"


VexNode::VexNode() = default;;

VexNode::VexNode(nodeKey key) : _key(std::move(key)) {};

void VexNode::traverse(std::function<void(VexNode &)> &&visit) {
    visit(*this);
    if (_nextNode != nullptr) {
        _nextNode->traverse(std::move(visit));
    }
}

template<typename T>
GraphNode<T>::GraphNode() = default;

template<typename T>
GraphNode<T>::GraphNode(nodeKey key, T val):_key(std::move(key)), _val(val) {};

template<typename T>
void GraphNode<T>::traverse(std::function<void(VexNode &)> &&visit) {
    if (_nextNode == nullptr) { return; }
    _nextNode->traverse(std::move(visit));
}


template<typename T>
GraphHead<T>::GraphHead() = default;

template<typename T>
GraphHead<T>::GraphHead(const nodeSet<T> &nodeSet, const arcSet &arcSet) {
    _nodeCount = 0;
    for (auto &&node:nodeSet) {
        insertVex(node);
    }
    for (auto &&arcArray:arcSet) {
        if (_nodeMap.find(arcArray[0] == _nodeMap.end()) || _nodeMap.find(arcArray[1]) == _nodeMap.end()) {
            throw std::runtime_error("Cannot Find" + arcArray[0] + " or" + arcArray[1]);
        }
        insertArc(arcSet[0], arcSet[1]);
    }
}

template<typename T>
GraphNode<T> &GraphHead<T>::locate(const nodeKey &key) {
    if (_nodeMap.find(key) == _nodeMap.end()) {
        throw std::runtime_error("Cannot find node");
    }
    return _nodeMap[key];
}

template<typename T>
void GraphHead<T>::insertVex(GraphNode<T> &&node) {
    if (_nodeMap.find(node._key) != _nodeMap.end()) {
        throw std::runtime_error("Find same key!");
    }
    _nodeMap[node._key] = std::move(node);
    _nodeCount++;
}

template<typename T>
void GraphHead<T>::insertArc(const nodeKey &firKey, const nodeKey &secKey) {
    auto &firNode = _nodeMap[firKey];
    auto firPtr = std::make_unique<VexNode>(firKey);
    firPtr->_nextNode = std::move(firNode._nextNode);
    firNode._nextNode = std::move(firPtr);
    auto &secNode = _nodeMap[secKey];
    auto secPtr = std::make_unique<VexNode>(secKey);
    secPtr->_nextNode = std::move(secNode._nextNode);
    secNode._nextNode = std::move(secPtr);
}

template<typename T>
void GraphHead<T>::assignVex(const nodeKey &key, T val) {
    locate(key)._val = val;
}

template<typename T>
void GraphHead<T>::removeSingleArc(const nodeKey &firKey, const nodeKey &secKey) {
    GraphNode<T> & node = locate(firKey);
    auto ptr = node._nextNode.get();
    if (ptr == nullptr) {
        return;
    }
    if (ptr->_key == secKey) {
        node._nextNode = std::move(ptr->_nextNode);
    }
    node.traverse([&secKey](VexNode &vexNode) {
        if (vexNode._nextNode->_key == secKey) {
            vexNode._nextNode = std::move(vexNode._nextNode->_nextNode);
        }
    });
//    while (ptr->_nextNode != nullptr) {
//        if (ptr->_nextNode->_key == secKey) {
//            ptr->_nextNode = std::move(ptr->_nextNode->_nextNode);
//            break;
//        }
//        ptr = ptr->_nextNode.get();
//    }
}

template<typename T>
void GraphHead<T>::removeArc(const nodeKey &firKey, const nodeKey &secKey) {
    removeSingleArc(firKey, secKey);
    removeSingleArc(secKey, firKey);
}

template<typename T>
void GraphHead<T>::removeVex(const nodeKey &key) {
//    auto ptr = locate(key)._nextNode.get();
//    while (ptr != nullptr) {
//        removeSingleArc(ptr->_key, key);
//        ptr = ptr->_nextNode.get();
//    }
    locate(key).traverse([this, &key](VexNode &vexNode) {
        this->removeSingleArc(vexNode._key, key);
    });
    _nodeMap.erase(key);
}

template<typename T>
const nodeKey &GraphHead<T>::firstAdjVex(const nodeKey &key) {
    return locate(key)._nextNode->_key;
}

template<typename T>
const nodeKey &GraphHead<T>::nextAdjVex(const nodeKey &key, const nodeKey &arcKey) {
//    auto ptr = locate(key)._nextNode.get();
//    while (ptr != nullptr) {
//        if (ptr->_key == arcKey) {
//            return key;
//        }
//        ptr = ptr->_nextNode.get();
//    }
    nodeKey targetKey;
    locate(key).traverse([&targetKey, &arcKey](VexNode &vexNode) {
        if (vexNode._key == arcKey) {
            if (vexNode._nextNode == nullptr) {
                throw std::runtime_error("The Next Node is undefined");
            }
            targetKey = vexNode._nextNode->_key;
        }
    });
    return locate(targetKey)._key;
}

template<typename T>
void GraphHead<T>::DFSTraverse(std::function<void(GraphNode<T> &)> &&visit) {
    auto visitStatus = std::unordered_map<nodeKey, bool>();
    auto visitStack = std::stack<GraphNode<T> *>();
    for (const auto &item : _nodeMap) {
        if (!visitStatus[item.second._key]) {
            visitStack.push(&item.second);
            visitStatus[item.second._key] = true;
        }
        while (!visitStack.empty()) {
//            auto curNode = visitStack.top(); //Why Delete???
            auto curNode = visitStack.top();
            visitStack.pop();
            visit(*curNode);
            auto ptr = curNode->_nextNode.get();
            while (ptr != nullptr) {
                if (!visitStatus[ptr->_key]) {
                    visitStack.push(&locate(ptr->_key));
                    visitStatus[ptr->_key] = true;
                }
                ptr = ptr->_nextNode.get();
            }
        }
    }
}

template<typename T>
void GraphHead<T>::BFSTraverse(std::function<void(GraphNode<T> &)> &&visit) {
    auto visitStatus = std::unordered_map<nodeKey, bool>();
    auto visitQueue = std::queue<GraphNode<T> *>();
    for (const auto &item : _nodeMap) {
        if (!visitStatus[item.second._key]) {
            visitQueue.push(&item.second);
            visitStatus[item.second._key] = true;
        }
        while (!visitQueue.empty()) {
            auto &curNode = visitQueue.front();
            visitQueue.pop();
            visit(*curNode);
            auto ptr = curNode->_nextNode.get();
            while (ptr != nullptr) {
                if (!visitStatus[ptr->_key]) {
                    visitQueue.push(&locate(ptr->_key));
                    visitStatus[ptr->_key] = true;
                }
                ptr = ptr->_nextNode.get();
            }
        }
    }
}