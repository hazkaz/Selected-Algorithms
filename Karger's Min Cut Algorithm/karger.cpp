#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <bits/stdc++.h>
#include "graph.h"
#include "string_utils.h"

using namespace std;
using graph::AssociativeEdge;
using graph::AssociativeGraph;
using graph::AssociativeNode;
using graph::printGraph;
using graph::readGraph;

void contractEdge(AssociativeGraph &g, size_t edgeIndex)
{
    // std::cout << edgeIndex;
    unordered_set<AssociativeEdge>::iterator edge_it = g.edges.begin();
    std::advance(edge_it, edgeIndex);

    int main_node_label = edge_it->ends.first;
    int secondary_node_label = edge_it->ends.second;

    g.nodes[main_node_label].connections.erase(g.nodes[main_node_label].connections.find(secondary_node_label));
    g.nodes[main_node_label].degree--;
    g.nodes[secondary_node_label].connections.erase(g.nodes[secondary_node_label].connections.find(main_node_label));
    g.nodes[secondary_node_label].degree--;

    for (int i : g.nodes[secondary_node_label].connections)
    {
        if (i != main_node_label)
        {
            g.nodes[main_node_label].connections.insert(i);
            g.nodes[main_node_label].degree++;

            g.nodes[i].connections.insert(main_node_label);
            g.nodes[i].connections.erase(secondary_node_label);

            // move edge from secondary to primary
            int min_node_label = min(g.nodes[main_node_label].name, i);
            int max_node_label = max(g.nodes[main_node_label].name, i);

            g.edges.insert(AssociativeEdge(min_node_label, max_node_label));

            // remove edge pointing to/from secondary
            min_node_label = min(secondary_node_label, i);
            max_node_label = max(secondary_node_label, i);

            AssociativeEdge edges_to_delete = AssociativeEdge(min_node_label, max_node_label);
            auto start = g.edges.equal_range(edges_to_delete);
            while (start.first != start.second)
            {
                if (*start.first == edges_to_delete)
                {
                    start.first = g.edges.erase(start.first);
                }
                else
                {
                    start.first++;
                }
            }
        }
    }
    if (g.nodes[main_node_label].connections.count(secondary_node_label))
        g.nodes[main_node_label].connections.erase(secondary_node_label);

    AssociativeEdge edgeToContract = AssociativeEdge(main_node_label, secondary_node_label);
    if (g.edges.count(edgeToContract))
    {
        auto start = g.edges.equal_range(edgeToContract);
        while (start.first != start.second)
        {
            start.first = g.edges.erase(start.first);
        }
    }

    g.nodes.erase(secondary_node_label);
}

int main()
{
    AssociativeGraph g;
    if (!readGraph("testGraph.txt", g.nodes, g.edges))
        return 1;
    int minCutValue = INT_MAX;
    int num_trials = g.nodes.size() * log(g.nodes.size());

    std::cout << "Running karger's min cut for " << num_trials << " trials!" << endl;
    for (int j = 0; j < num_trials; j++)
    {
        std::random_device dev;
        std::mt19937 rng(dev());

        AssociativeGraph g;
        if (!readGraph("testGraph.txt", g.nodes, g.edges))
            return 1;
        // printGraph(g, cout);
        while (g.nodes.size() > 2)
        {
            std::uniform_int_distribution<std::mt19937::result_type> randEdge(0, g.edges.size() - 1);
            contractEdge(g, randEdge(rng));
        }
        // printGraph(g, cout);
        std::cout << j + 1 << ". Last Min cut value - " << g.edges.size() << " Lowest Min cut value - " << minCutValue << endl;
        if (g.edges.size() < minCutValue)
        {
            minCutValue = g.edges.size();
        }
    }

    std::cout << "Best Guess - " << minCutValue << endl;

    return 0;
}