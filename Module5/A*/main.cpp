//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  main.cpp

#include <iostream>
#include "Graph.h"
#include <vector>
#include <algorithm>
#include "math.h"

using namespace std;

vector<Node*> nodes, nodes2;

vector<vector<int> > createMatrix(int n) {
    vector<vector<int> > matrix;
    for (int i = 0; i < n; i++) {
        vector<int> row;
        for (int j = 0; j < n; j++) {
            Node *node = new Node(j);
            int value;
            cin >> value;
            row.push_back(value);
            node->x = i;
            node->y = j;
            nodes.push_back(node);
        }
        matrix.push_back(row);
    }
    return matrix;
}

int main() {
    cout << "Introduce matriz: ";
    int n;
    cin >> n;
    vector<vector<int> > matrix = createMatrix(n);
    cout << "\nMatriz: " << endl;
    // Graph *G = new Graph(matrix);
    // print matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    Graph *g = new Graph(nodes, matrix);
    vector<Node*> AStar = g->runAStar(nodes[0], nodes[nodes.size() - 1]);
    cout << "\nAStar: " << endl;
    for (int i = 0; i < AStar.size(); i++) {
        cout << AStar[i]->number << ": (" << AStar[i]->x << ", " << AStar[i]->y << ")"<< endl;
    }
}

/*
4
1 0 0 0
1 1 0 1
1 1 0 0
0 1 1 1
*/