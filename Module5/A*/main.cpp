//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  main.cpp

#include <iostream>
#include "Graph.h"
#include <vector>
#include <algorithm>

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

bool isSafe(int x, int y, int rows, int columns) { // checking the boundry
    return (x >= 0 && x < rows && y >= 0 && y < columns);
}

Node* findNode(int x, int y) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->x == x && nodes[i]->y == y) {
            return nodes[i];
        }
    }
    return NULL;
}


void checkNeighbours(Node *n, vector<vector<int> > matrix) {
    int rows = matrix.size();
    int columns = matrix[0].size();
        // Considering only 4 directions up, down , right, left                    
        int count = 0;
        if (matrix[n->x][n->y] == 1) { // if the current node is not a wall
            if(isSafe(n->x - 1, n->y, rows, columns)) { // left
                if(matrix[n->x - 1][n->y] == 1) {
                    count ++;
                    n->neighbors.push_back(findNode(n->x - 1, n->y));
                }
            }

            if(isSafe(n->x - 1, n->y - 1, rows, columns)) { // left-up
                if(matrix[n->x - 1][n->y - 1] == 1) {
                    count ++;
                    n->neighbors.push_back(findNode(n->x - 1, n->y - 1));
                }
            }

            if(isSafe(n->x, n->y - 1, rows, columns)) { // up
                if(matrix[n->x][n->y - 1] == 1) {
                    count ++;
                    n->neighbors.push_back(findNode(n->x, n->y - 1));
                }
            }

            if(isSafe(n->x + 1, n->y - 1, rows, columns)) { // right-up
                if(matrix[n->x + 1][n->y - 1] == 1) {
                    count ++;
                    n->neighbors.push_back(findNode(n->x + 1, n->y - 1));
                }
            }

            if(isSafe(n->x + 1, n->y, rows, columns)) { // right
                if(matrix[n->x + 1][n->y] == 1) {
                    count ++;
                    n->neighbors.push_back(findNode(n->x + 1, n->y));
                }
            } 

            if(isSafe(n->x + 1, n->y + 1, rows, columns)) { // right-down
                if(matrix[n->x + 1][n->y + 1] == 1) {
                    count ++;
                    n->neighbors.push_back(findNode(n->x + 1, n->y + 1));
                }
            }

            if(isSafe(n->x, n->y + 1, rows, columns)) { // down
                if(matrix[n->x][n->y + 1] == 1) {
                    count ++;
                    n->neighbors.push_back(findNode(n->x, n->y + 1));
                }
            }

            if(isSafe(n->x - 1, n->y + 1, rows, columns)) { // left-down
                if(matrix[n->x - 1][n->y + 1] == 1) {
                    count ++;
                    n->neighbors.push_back(findNode(n->x - 1, n->y + 1));
                }
            }
        }

        cout << "Node " << n->number << " has " << count << " neighbors" << endl;
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

    cout << "\nNodes: " << endl;
    vector<Node*>::iterator ni;
    for(ni = nodes.begin(); ni != nodes.end(); ni++) {
        if (matrix[(*ni)->x][(*ni)->y] == 1) {
            // cout << "Node " << (*ni)->number << " has coordinates (" << (*ni)->x << ", " << (*ni)->y << ")" << endl;
            checkNeighbours(*ni, matrix);
            nodes2.push_back(*ni);
        }
    }
    
    // print nodes2
    cout << "\nNodes2: " << endl;
    vector<Node*>::iterator ni2;
    for(ni2 = nodes2.begin(); ni2 != nodes2.end(); ni2++) {
        cout << "Node " << (*ni2)->number << " has coordinates (" << (*ni2)->x << ", " << (*ni2)->y << ")" << endl;
        // cout << "Node " << (*ni2)->number << " has " << (*ni2)->neighbors.size() << " neighbors" << endl;
    }

    Graph *g = new Graph(nodes2);
    vector<Node*> AStar = g->runAStar(nodes2[0], nodes2[nodes2.size() - 1]);
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