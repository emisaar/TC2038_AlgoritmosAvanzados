//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
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
        Node *s;

        Graph(vector<Node*> _nodes, vector<Edge*> _edges);

        vector <Node*> getNeighbors(Node *n);
        void printDijkstra();
        void printFloyd(vector<vector<int> > matrix);
        void runDijkstra(Node *source);
        void runFloyd();
        Node *getMinDist(vector<Node*> qs);
        void remove(vector<Node*> &qs, Node *q);
        int getLength(Node *u, Node *v);
};