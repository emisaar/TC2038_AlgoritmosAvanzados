//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  Graph.h

#pragma once
#include "Node.h"
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
        Node *goal;

        Graph(vector<Node*> _nodes, vector<Edge*> _edges);

        vector <Node*> getNeighbors(Node *n);
        void printDijkstra();
        void printFloyd(vector<vector<int> > matrix);
        void runDijkstra(Node *source);
        void runFloyd();
        Node *getMinF(vector<Node*> qs);
        vector<Node*> constructPath(Node *goal);
        void remove(vector<Node*> &qs, Node *q);
        int getLength(Node *u, Node *v);

        vector<Node*> runAStar(Node *source, Node *goal);
        float heuristic(Node *u, Node *v);
        vector<Node*> neighbors(Node *n);

        Graph(vector<Node*> _nodes); 
};