//  Actividad 5.5 Implementación A*
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 28/11/2022

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