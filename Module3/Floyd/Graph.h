#pragma once
#include "Edge.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Graph {
    public:
        vector<Node*> nodes;
        vector<Edge*> edges;

        Graph(vector<Node*> _nodes, vector<Edge*> _edges);

        vector <Node*> getNeighbors(Node *n);
        void print();
        void runDijkstra(Node *source);
        Node *getMinDist(vector<Node*> qs);
        void remove(vector<Node*> &qs, Node *q);
        int getLength(Node *u, Node *v);
};