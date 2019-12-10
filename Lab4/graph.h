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
#include <stack>
#include <utility>
#include <queue>

using nodeKey=std::string;

template<typename T>
class GraphHead;

template<typename T>
class GraphNode;

class VexNode {
private:
    nodeKey _key;

    std::unique_ptr<VexNode> _nextNode;

public://Why???Define inline is ok,but in cpp is multiple???

    VexNode();

    explicit VexNode(nodeKey key);

    [[nodiscard]] inline const nodeKey &key() const { return _key; };

    void traverse(std::function<void(VexNode &)> &&visit);

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

    void traverse(std::function<void(VexNode &)> &&);

    inline const T &val() const { return _val; };

    inline const nodeKey &key() const { return _key; };

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

    void removeSingleArc(const nodeKey &, const nodeKey &);

public:
    GraphHead();

    GraphHead(const nodeSet<T> &, const arcSet &);

    inline void clear() { _nodeMap.clear(); };

    GraphNode<T> &locate(const nodeKey &);

    void assignVex(const nodeKey &, T);

    const nodeKey &firstAdjVex(const nodeKey &);

    const nodeKey &nextAdjVex(const nodeKey &, const nodeKey &);

    void insertVex(GraphNode<T> &&);

    void removeVex(const nodeKey &);

    void insertArc(const nodeKey &, const nodeKey &);

    void removeArc(const nodeKey &, const nodeKey &);

    void save(std::string &&);

    void load(std::string &&);

    void DFSTraverse(std::function<void(GraphNode<T> &)> &&);

    void BFSTraverse(std::function<void(GraphNode<T> &)> &&);
};

#endif //LAB4_GRAPH_H
