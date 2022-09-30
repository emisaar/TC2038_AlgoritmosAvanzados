//  Actividad 3.2 - Implementación de "Dijkstra" y Floyd
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  Graph.h

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