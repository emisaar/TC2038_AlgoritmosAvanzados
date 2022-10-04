//  Actividad 3.2 - Implementación de "Dijkstra" y Floyd
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  main.cpp

#include <iostream>
#include "Graph.h"
#include <vector>

using namespace std;

vector<vector<int> > createMatrix(int n) {
    vector<vector<int> > matrix;
    for (int r = 0; r < n; r++) {
        vector<int> row;
        for (int c = 0; c < n; c++) {
            int a = 0;
            cout << "Peso[" << r + 1 << "][" << c + 1 << "]: ";
            cin >> a;
            cout << endl;
            row.push_back(a);
        }
    matrix.push_back(row);
    }
    return matrix;
}

int main() {
    int n;
    cout << "Introduce el número de nodos: ";
    cin >> n;

    int w;
    cout << "Introduce los pesos del grafo." << endl;
    vector<vector<int> > weightMatrix = createMatrix(n);

    cout << "Matriz de entrada" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << weightMatrix[i][j] << "|";
        }
        cout << endl;
    }

    vector<Node*> nodes;
    vector<Node*>::iterator niD;
    vector<Edge*> edges;
    vector<Edge*>::iterator eiD;

    for(int i = 0; i < n; i++) {
        Node *N = new Node(i + 1);
        nodes.push_back(N);
    }

    for(int i = 0; i < weightMatrix.size(); i++) {
        for(int j = 0; j < weightMatrix[0].size(); j++) {
            if(weightMatrix[i][j] != -1 && weightMatrix[i][j] != 0) {
                edges.push_back(new Edge(nodes[i], nodes[j], weightMatrix[i][j]));
            }
        }
    }

    cout << "Dijkstra" << endl;
    Graph *g = new Graph(nodes, edges);
    for(int i = 0; i < nodes.size(); i++) {
        g->runDijkstra(nodes[i]);
        for(int j = 0; j < nodes.size(); j++) {
            cout << "Node " << nodes[i]->number << " to node: " << nodes[j]->number << " Dist: " << nodes[j]->distance << endl;
        }
        cout << endl;
    }
    // g->runDijkstra(nodes[0]);
    // g->print();

    cout << "Floyd" << endl;
    Graph *gFloyd = new Graph(nodes, edges);
    gFloyd->runFloyd();

    // Node *n1 = new Node(1);
    // Node *n2 = new Node(2);
    // Node *n3 = new Node(3);
    // Node *n4 = new Node(4);
    // Node *n5 = new Node(5);
    // Node *n6 = new Node(6);
    // nodes.push_back(n1);
    // nodes.push_back(n2);
    // nodes.push_back(n3);
    // nodes.push_back(n4);
    // nodes.push_back(n5);
    // nodes.push_back(n6);

    // edges.push_back(new Edge(n1, n2, 6));
    // edges.push_back(new Edge(n1, n3, 2));
    // edges.push_back(new Edge(n1, n6, 12));
    // edges.push_back(new Edge(n2, n3, 7));
    // edges.push_back(new Edge(n2, n4, 13));
    // edges.push_back(new Edge(n3, n6, 1));
    // edges.push_back(new Edge(n3, n4, 10));
    // edges.push_back(new Edge(n4, n5, 5));
    // edges.push_back(new Edge(n5, n6, 8));

    // Graph *g = new Graph(nodes, edges);

    // g->print();
    // g->runDijkstra(n1);
    // cout << "----------------" << endl;
    // g->print();

    // vector<Node*> nodesFloyd;
    // vector<Edge*> edgesFloyd;

    // Node *n1F = new Node(1);
    // Node *n2F = new Node(2);
    // Node *n3F = new Node(3);
    // Node *n4F = new Node(4);
    // nodesFloyd.push_back(n1F);
    // nodesFloyd.push_back(n2F);
    // nodesFloyd.push_back(n3F);
    // nodesFloyd.push_back(n4F);

    // edgesFloyd.push_back(new Edge(n1F, n2F, 2));
    // edgesFloyd.push_back(new Edge(n1F, n3F, 2));
    // edgesFloyd.push_back(new Edge(n1F, n4F, 3));
    // edgesFloyd.push_back(new Edge(n2F, n1F, 2));
    // edgesFloyd.push_back(new Edge(n2F, n3F, 1));
    // edgesFloyd.push_back(new Edge(n2F, n4F, 5));
    // edgesFloyd.push_back(new Edge(n3F, n1F, 2));
    // edgesFloyd.push_back(new Edge(n3F, n2F, 1));
    // edgesFloyd.push_back(new Edge(n3F, n4F, 4));
    // edgesFloyd.push_back(new Edge(n4F, n1F, 3));
    // edgesFloyd.push_back(new Edge(n4F, n2F, 5));
    // edgesFloyd.push_back(new Edge(n4F, n3F, 4));

    // Graph *gF = new Graph(nodesFloyd, edgesFloyd);

    // cout << "Floyd" << endl;
    // gF->runFloyd();

    return 0;
}