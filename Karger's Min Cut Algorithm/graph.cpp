#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "string_utils.h"

namespace graph
{
    AssociativeNode::AssociativeNode(int n)
    {
        this->name = n;
        this->degree = 0;
    }

    AssociativeNode::AssociativeNode(){

    }

    AssociativeEdge::AssociativeEdge(int here, int there)
    {
        this->ends.first = here;
        this->ends.second = there;
    }

    bool AssociativeNode::operator==(const AssociativeNode &n)
    {
        return this->name == n.name;
    }

    bool AssociativeEdge::operator==(const AssociativeEdge &n)
    {
        return this->ends.first == n.ends.first && this->ends.second == n.ends.second;
    }

    bool operator==(const AssociativeNode &n1, const AssociativeNode &n2)
    {
        return n1.name == n2.name;
    }
    bool operator==(const AssociativeEdge &e1, const AssociativeEdge &e2)
    {
        return e1.ends.first == e2.ends.first && e1.ends.second == e2.ends.second;
    }

    VectorNode::VectorNode(int n)
    {
        this->name = n;
        this->degree = 0;
    }

    bool VectorNode::operator==(const VectorNode n)
    {
        return this->name == n.name;
    }

    VectorEdge::VectorEdge(int i, int j)
    {
        this->ends = {i, j};
    }

    bool readGraph(std::string fileName, std::vector<VectorNode> &nodes, std::vector<VectorEdge> &edges)
    {
        try
        {
            std::ifstream graphData;
            graphData.open(fileName);
            std::string line;
            while (std::getline(graphData, line))
            {
                std::vector<std::string> adjacent;
                adjacent = split(line.substr(0, line.size() - 1), "\t");
                std::vector<int> c;
                VectorNode n = VectorNode(stoi(adjacent[0]));

                for (auto i = next(adjacent.begin()); i != adjacent.end(); ++i)
                {
                    int here = n.name;

                    int there = stoi(*i);
                    if (here < there)
                    {
                        VectorEdge e = VectorEdge(here, there);
                        edges.push_back(e);
                    }
                    n.connections.push_back(there);
                    n.degree++;
                }
                nodes.push_back(n);
            }
            graphData.close();
        }
        catch (int e)
        {
            return false;
        }
        return true;
    }

    void printGraph(VectorGraph &g, std::ostream &o)
    {
        o << "xxx" << std::endl;
        for (auto i : g.edges)
        {
            o << i.ends.first << "<->" << i.ends.second << std::endl;
        }
        for (auto i : g.nodes)
        {
            o << i.name << "===";
            for (auto j : i.connections)
            {
                o << j << "-";
            }
            o << std::endl;
        }
        o << "xxx" << std::endl
          << std::endl;
    }

    bool readGraph(std::string fileName, std::unordered_map<int, AssociativeNode> &nodes, std::unordered_multiset<AssociativeEdge> &edges)
    {
        try
        {
            std::ifstream graphData;
            graphData.open(fileName);
            std::string line;
            while (std::getline(graphData, line))
            {
                std::vector<std::string> adjacent;
                adjacent = split(line.substr(0, line.size() - 1), "\t");
                std::vector<int> c;
                AssociativeNode n = AssociativeNode(stoi(adjacent[0]));

                for (auto i = next(adjacent.begin()); i != adjacent.end(); ++i)
                {
                    int here = n.name;
                    int there = stoi(*i);
                    if (here < there)
                    {
                        AssociativeEdge e = AssociativeEdge(here, there);
                        edges.insert(e);
                    }
                    n.connections.insert(there);
                    n.degree++;
                }
                nodes[n.name] = n;
            }
            graphData.close();
        }
        catch (int e)
        {
            return false;
        }
        return true;
    }

    void printGraph(AssociativeGraph &g, std::ostream &o)
    {
        o << "xxx" << std::endl;
        for (auto i : g.edges)
        {
            o << i.ends.first << "<->" << i.ends.second << std::endl;
        }
        for (auto i : g.nodes)
        {
            o << i.first << "===";
            for (auto j : i.second.connections)
            {
                o << j << "-";
            }
            o << std::endl;
        }
        o << "xxx" << std::endl
          << std::endl;
    }

};
