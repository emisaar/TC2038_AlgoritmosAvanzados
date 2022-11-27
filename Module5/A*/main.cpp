//  Actividad 5.5 Implementación A*
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 28/11/2022

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
            string value;
            cin >> value;
            row.push_back(stoi(value));
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
    // cout << "\nMatriz: " << endl;
    // // print matrix
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << endl;
    cout << "====== AStar ======" << endl;
    Graph *g = new Graph(nodes, matrix);
    vector<Node*> AStar = g->runAStar(nodes[0], nodes[nodes.size() - 1]);
    cout << endl;
    cout << "\tPath coords:";
    for (int i = 0; i < AStar.size(); i++) {
        cout << "(" << AStar[i]->x << ", " << AStar[i]->y << ") ";
    }
    cout << endl;
}

/*
4
1 0 0 0
1 1 0 1
1 1 0 0
0 1 1 1
*/

/*

4
1, 0, 0, 0
1, 1, 0, 1
1, 1, 0, 0
0, 1, 1, 1*/

/*
10
1 1 1 1 1 0 0 0 0 0
0 0 1 0 1 0 0 0 0 0
0 0 1 0 1 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 0 1 1 1 1 0 0
0 0 0 0 1 0 0 1 0 0
0 0 0 0 1 1 1 1 1 0
0 0 0 0 1 0 0 0 1 0
0 0 0 0 0 0 0 0 1 1
*/