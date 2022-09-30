#pragma once
#include "Node.h"

class Edge {
    public: 
        Node *first;
        Node *second;
        int weight;

        Edge(Node *_first, Node *_second, int _weight);
};