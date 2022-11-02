//  Actividad 3.3
//  Flujo Máximo

//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258

//  Fecha: 17/10/2022

/* Referencias:
https://brilliant.org/wiki/ford-fulkerson-algorithm/
https://emory.gitbook.io/dsa-java/network-flow/ford-fulkerson-algorithm
https://favtutor.com/blogs/ford-fulkerson-algorithm
https://github.com/fit-coder/fitcoderyoutube/blob/master/graph/ford_fulkerson.cpp
https://www.programiz.com/dsa/ford-fulkerson-algorithm
https://github.com/BedirT/Algorithms_and_DS/blob/master/Algorithms/Graph/Ford%20Fulkerson.cpp
https://www.youtube.com/watch?v=_UcOALraATY
*/

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
        Node *source;

        Graph(vector<Node*> _nodes, vector<Edge*> _edges);

        vector <Node*> getNeighbors(Node *n);
        void printGraph();
        void printFloyd(vector<vector<int> > matrix);

        void runDijkstra(Node *source);
        void runFloyd();
        
        int runFordFulkerson(Node *source, Node *sink);
        Edge *findEdge(Node *u, Node *v);
        int getMaxDist(vector<Edge*> qs);
        bool bfs(Node *s, Node *t);
        
        Node *getMinDist(vector<Node*> qs);
        void remove(vector<Node*> &qs, Node *q);
        int getLength(Node *u, Node *v);

        void findPaths(Node *s, Node *t, vector<int> &weights, vector<int> &values);
};