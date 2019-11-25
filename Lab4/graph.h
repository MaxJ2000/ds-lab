//
// Created by john on 11/25/19.
//

#ifndef LAB4_GRAPH_H
#define LAB4_GRAPH_H


#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include <array>
#include <utility>


using nodeKey=std::string;

template<typename T>
class GraphHead;

template<typename T>
class GraphNode;

class VexNode {
private:
    nodeKey _key;

    std::unique_ptr<VexNode> _nextNode;

    inline VexNode *_next() { return _nextNode.get(); };

public:
    VexNode();

    explicit VexNode(nodeKey);

    template<typename T>
    friend
    class GraphNode;

    template<typename T>
    friend
    class GraphHead;
};

template<typename T>
class GraphNode {
private:
    T _val;

    nodeKey _key;

    std::unique_ptr<VexNode> _nextNode;
public:
    GraphNode();

    GraphNode(nodeKey, T);

    inline const nodeKey &key() { return _key };

    friend class GraphHead<T>;
};

template<typename T>
using nodeSet=std::vector<GraphNode<T>>;

using arcSet=std::vector<std::array<nodeKey, 2>>;

template<typename T>
class GraphHead {
private:
    std::unordered_map<nodeKey, GraphNode<T>> _nodeMap;

    int _nodeCount;

    void removeSingleArc(const nodeKey &,const  nodeKey &);

public:
    GraphHead();

    GraphHead(nodeSet<T>, arcSet);

    inline void clear() { _nodeMap.clear(); };

    GraphNode<T> &locate(nodeKey &);

    void assignVex(nodeKey &, T);

    const nodeKey &firstAdjVex(nodeKey &);

    const nodeKey &nextAdjVex(nodeKey &, nodeKey &);

    void insertVex(GraphNode<T> &&);

    void removeVex(nodeKey &);

    void insertArc(nodeKey, nodeKey);

    void removeArc(const nodeKey&, const nodeKey&);

    void DFSTraverse(std::function<void(GraphNode<T> &)>);

    void BFSTraverse(std::function<void(GraphNode<T> &)>);
};

#endif //LAB4_GRAPH_H
