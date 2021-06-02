#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "string_utils.h"

namespace graph
{

    class AssociativeNode
    {
    public:
        int name;
        std::unordered_multiset<int> connections;
        int degree;
        AssociativeNode();
        AssociativeNode(int n);
        std::unordered_set<int> merged;
        bool operator==(const AssociativeNode &n);
    };

    class AssociativeEdge
    {
    public:
        AssociativeEdge(int here, int there);
        std::pair<int, int> ends;
        bool operator==(const AssociativeEdge &e);
    };

    class VectorNode
    {
    public:
        int name;
        std::vector<int> connections;
        int degree;
        VectorNode(int n);
        bool operator==(const VectorNode n);
    };

    class VectorEdge
    {
    public:
        std::pair<int, int> ends;
        VectorEdge(int i, int j);
    };
    class VectorGraph
    {
    public:
        std::vector<VectorNode> nodes;
        std::vector<VectorEdge> edges;
    };
    class AssociativeGraph;

    bool readGraph(std::string fileName, std::vector<VectorNode> &nodes, std::vector<VectorEdge> &edges);
    void printGraph(VectorGraph &g, std::ostream &o);

    bool readGraph(std::string fileName, std::unordered_map<int, AssociativeNode> &nodes, std::unordered_multiset<AssociativeEdge> &edges);
    void printGraph(AssociativeGraph &g, std::ostream &o);

    bool operator==(const AssociativeNode &n1, const AssociativeNode &n2);
    bool operator==(const AssociativeEdge &e1, const AssociativeEdge &e2);
}

namespace std
{
    template <>
    struct hash<graph::AssociativeEdge>
    {
        std::size_t operator()(const graph::AssociativeEdge &e) const
        {
            // smaller node name
            return hash<int>{}(e.ends.first);
        }
    };

    template <>
    struct hash<graph::AssociativeNode>
    {
        std::size_t operator()(const graph::AssociativeNode &n) const
        {
            return hash<int>{}(n.name);
        }
    };
}

namespace graph
{
    class AssociativeGraph
    {
    public:
        std::unordered_map<int, AssociativeNode> nodes;
        std::unordered_multiset<AssociativeEdge> edges;
    };

}