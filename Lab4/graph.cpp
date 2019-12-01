//
// Created by john on 11/25/19.
//

#include <fstream>
#include "graph.h"

VexNode::VexNode() = default;


VexNode::VexNode(nodeKey key) : _key(std::move(key)) {}


void VexNode::traverse(std::function<void(VexNode &)> &&visit){
    visit(*this);
    if (_nextNode != nullptr) {
        _nextNode->traverse(std::move(visit));
    }
}

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
        insertArc(arcArray[0], arcArray[1]);
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
    auto firPtr = std::make_unique<VexNode>(secKey);
    firPtr->_nextNode = std::move(firNode._nextNode);
    firNode._nextNode = std::move(firPtr);
    auto &secNode = _nodeMap[secKey];
    auto secPtr = std::make_unique<VexNode>(firKey);
    secPtr->_nextNode = std::move(secNode._nextNode);
    secNode._nextNode = std::move(secPtr);
}

template<typename T>
void GraphHead<T>::assignVex(const nodeKey &key, T val) {
    locate(key)._val = val;
}

template<typename T>
void GraphHead<T>::removeSingleArc(const nodeKey &firKey, const nodeKey &secKey) {
    auto &node = locate(firKey);
    auto ptr = node._nextNode.get();
    if (ptr == nullptr) {
        return;
    }
    if (ptr->_key == secKey) {
        node._nextNode = std::move(ptr->_nextNode);
    }
    node.traverse([&secKey](VexNode &vexNode) {
        if (vexNode._nextNode != nullptr && vexNode._nextNode->_key == secKey) {
            vexNode._nextNode = std::move(vexNode._nextNode->_nextNode);
        }
    });
}

template<typename T>
void GraphHead<T>::removeArc(const nodeKey &firKey, const nodeKey &secKey) {
    removeSingleArc(firKey, secKey);
    removeSingleArc(secKey, firKey);
}

template<typename T>
void GraphHead<T>::removeVex(const nodeKey &key) {
    locate(key).traverse([&key, this](VexNode &vexNode) {
        removeSingleArc(vexNode._key, key);
    });//Illegal to use lambda to change this element!only use for locate and read
    _nodeMap.erase(key);
}

template<typename T>
const nodeKey &GraphHead<T>::firstAdjVex(const nodeKey &key) {
    return locate(key)._nextNode->_key;
}

template<typename T>
const nodeKey &GraphHead<T>::nextAdjVex(const nodeKey &key, const nodeKey &arcKey) {
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
    auto visitStack = std::stack<nodeKey>();
    for (const auto &item : _nodeMap) {
        if (!visitStatus[item.second._key]) {
            visitStack.push(item.second._key);
            visitStatus[item.second._key] = true;
        }
        while (!visitStack.empty()) {
            auto curKey = std::move(visitStack.top());
            visitStack.pop();
            visit(locate(curKey));
            locate(curKey).traverse([&visitStack, &visitStatus](VexNode &vexNode) {
                if (!visitStatus[vexNode.key()]) {
                    visitStack.push(vexNode.key());
                    visitStatus[vexNode.key()] = true;
                }
            });
        }
    }
}

template<typename T>
void GraphHead<T>::BFSTraverse(std::function<void(GraphNode<T> &)> &&visit) {
    auto visitStatus = std::unordered_map<nodeKey, bool>();
    auto visitQueue = std::queue<nodeKey>();
    for (const auto &item : _nodeMap) {
        if (!visitStatus[item.second._key]) {
            visitQueue.push(item.second._key);
            visitStatus[item.second._key] = true;
        }
        while (!visitQueue.empty()) {
            auto curKey = std::move(visitQueue.front());
            visitQueue.pop();
            visit(locate(curKey));
            locate(curKey).traverse([&visitQueue, &visitStatus](VexNode &vexNode) {
                if (!visitStatus[vexNode.key()]) {
                    visitQueue.push(vexNode.key());
                    visitStatus[vexNode.key()] = true;
                }
            });
        }
    }
}

template<typename T>
void GraphHead<T>::save(std::string &&file) {
    auto visitStatus = std::unordered_map<nodeKey, bool>();
    std::ofstream fs;
    fs.open(file + "VexSet.sav");
    for (const auto &item : _nodeMap) {
        fs << item.first << std::endl;
        fs << item.second.val() << std::endl;
    }
    fs.close();
    fs.open(file + "ArcSet.sav");
    for (const auto &item : _nodeMap) {
        locate(item.second.key()).traverse([&item, &fs, &visitStatus](VexNode &vexNode) {
            if (!visitStatus[vexNode.key()]) {
                fs << item.second.key() << "," << vexNode.key() << std::endl;
            }
        });
        visitStatus[item.second.key()] = true;
    }
    fs.close();
}

template<typename T>
void GraphHead<T>::load(std::string &&file) {
    _nodeMap.clear();
    _nodeCount = 0;
    std::ifstream fs;
    nodeKey keyBuf, arcKeyBuf;
    T valBuf;
    fs.open(file + "VexSet.sav");
    while (fs >> keyBuf >> valBuf) {
        insertVex(GraphNode<T>(keyBuf, valBuf));
    }ﾟωﾟﾉ= /｀ｍ´）ﾉ ~┻━┻   //*´∇｀*/ ['_']; o=(ﾟｰﾟ)  =_=3; c=(ﾟΘﾟ) =(ﾟｰﾟ)-(ﾟｰﾟ); (ﾟДﾟ) =(ﾟΘﾟ)= (o^_^o)/ (o^_^o);(ﾟДﾟ)={ﾟΘﾟ: '_' ,ﾟωﾟﾉ : ((ﾟωﾟﾉ==3) +'_') [ﾟΘﾟ] ,ﾟｰﾟﾉ :(ﾟωﾟﾉ+ '_')[o^_^o -(ﾟΘﾟ)] ,ﾟДﾟﾉ:((ﾟｰﾟ==3) +'_')[ﾟｰﾟ] }; (ﾟДﾟ) [ﾟΘﾟ] =((ﾟωﾟﾉ==3) +'_') [c^_^o];(ﾟДﾟ) ['c'] = ((ﾟДﾟ)+'_') [ (ﾟｰﾟ)+(ﾟｰﾟ)-(ﾟΘﾟ) ];(ﾟДﾟ) ['o'] = ((ﾟДﾟ)+'_') [ﾟΘﾟ];(ﾟoﾟ)=(ﾟДﾟ) ['c']+(ﾟДﾟ) ['o']+(ﾟωﾟﾉ +'_')[ﾟΘﾟ]+ ((ﾟωﾟﾉ==3) +'_') [ﾟｰﾟ] + ((ﾟДﾟ) +'_') [(ﾟｰﾟ)+(ﾟｰﾟ)]+ ((ﾟｰﾟ==3) +'_') [ﾟΘﾟ]+((ﾟｰﾟ==3) +'_') [(ﾟｰﾟ) - (ﾟΘﾟ)]+(ﾟДﾟ) ['c']+((ﾟДﾟ)+'_') [(ﾟｰﾟ)+(ﾟｰﾟ)]+ (ﾟДﾟ) ['o']+((ﾟｰﾟ==3) +'_') [ﾟΘﾟ];(ﾟДﾟ) ['_'] =(o^_^o) [ﾟoﾟ] [ﾟoﾟ];(ﾟεﾟ)=((ﾟｰﾟ==3) +'_') [ﾟΘﾟ]+ (ﾟДﾟ) .ﾟДﾟﾉ+((ﾟДﾟ)+'_') [(ﾟｰﾟ) + (ﾟｰﾟ)]+((ﾟｰﾟ==3) +'_') [o^_^o -ﾟΘﾟ]+((ﾟｰﾟ==3) +'_') [ﾟΘﾟ]+ (ﾟωﾟﾉ +'_') [ﾟΘﾟ]; (ﾟｰﾟ)+=(ﾟΘﾟ); (ﾟДﾟ)[ﾟεﾟ]='\\'; (ﾟДﾟ).ﾟΘﾟﾉ=(ﾟДﾟ+ ﾟｰﾟ)[o^_^o -(ﾟΘﾟ)];(oﾟｰﾟo)=(ﾟωﾟﾉ +'_')[c^_^o];(ﾟДﾟ) [ﾟoﾟ]='\"';(ﾟДﾟ) ['_'] ( (ﾟДﾟ) ['_'] (ﾟεﾟ+(ﾟДﾟ)[ﾟoﾟ]+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ (ﾟｰﾟ)+ (ﾟΘﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((ﾟｰﾟ) + (ﾟΘﾟ))+ (ﾟｰﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ (ﾟｰﾟ)+ ((ﾟｰﾟ) + (ﾟΘﾟ))+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((o^_^o) +(o^_^o))+ ((o^_^o) - (ﾟΘﾟ))+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((o^_^o) +(o^_^o))+ (ﾟｰﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+((ﾟｰﾟ) + (ﾟΘﾟ))+ (c^_^o)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟｰﾟ)+ ((o^_^o) - (ﾟΘﾟ))+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ (ﾟΘﾟ)+ (c^_^o)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ (ﾟｰﾟ)+ ((ﾟｰﾟ) + (ﾟΘﾟ))+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((ﾟｰﾟ) + (ﾟΘﾟ))+ (ﾟｰﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((ﾟｰﾟ) + (ﾟΘﾟ))+ (ﾟｰﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((ﾟｰﾟ) + (ﾟΘﾟ))+ ((ﾟｰﾟ) + (o^_^o))+ (ﾟДﾟ)[ﾟεﾟ]+((ﾟｰﾟ) + (ﾟΘﾟ))+ (ﾟｰﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟｰﾟ)+ (c^_^o)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ (ﾟΘﾟ)+ ((o^_^o) - (ﾟΘﾟ))+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ (ﾟｰﾟ)+ (ﾟΘﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((o^_^o) +(o^_^o))+ ((o^_^o) +(o^_^o))+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ (ﾟｰﾟ)+ (ﾟΘﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((o^_^o) - (ﾟΘﾟ))+ (o^_^o)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ (ﾟｰﾟ)+ (o^_^o)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((o^_^o) +(o^_^o))+ ((o^_^o) - (ﾟΘﾟ))+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((ﾟｰﾟ) + (ﾟΘﾟ))+ (ﾟΘﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((o^_^o) +(o^_^o))+ (c^_^o)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟΘﾟ)+ ((o^_^o) +(o^_^o))+ (ﾟｰﾟ)+ (ﾟДﾟ)[ﾟεﾟ]+(ﾟｰﾟ)+ ((o^_^o) - (ﾟΘﾟ))+ (ﾟДﾟ)[ﾟεﾟ]+((ﾟｰﾟ) + (ﾟΘﾟ))+ (ﾟΘﾟ)+ (ﾟДﾟ)[ﾟoﾟ]) (ﾟΘﾟ)) ('_');
    fs.close();
    fs.open(file + "ArcSet.sav");
    while (getline(fs, keyBuf, ',') && getline(fs, arcKeyBuf)) {
        insertArc(keyBuf, arcKeyBuf);
    }
    fs.close();
}

