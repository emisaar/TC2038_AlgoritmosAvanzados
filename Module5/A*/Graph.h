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
#include <string>

using namespace std;

class Graph {
    public:
        vector<Node*> nodes;
        vector<Edge*> edges;

        vector<vector<int> > matrix;

        Node *s;
        Node *goal;

        Graph(vector<Node*> _nodes, vector<vector<int> > _matrix); 
        
        vector<Node*> runAStar(Node *source, Node *goal);
        float heuristic(Node *u, Node *v);
        Node *getMinF(vector<Node*> qs);
        vector<Node*> constructPath(Node *goal);

        void constructStringPath(vector<Node*> &path);

        void remove(vector<Node*> &qs, Node *q);

        Node *findNode(int x, int y);
        bool isSafe(int x, int y, int rows, int columns);
        void getNodeNeighbors(Node *n);

};