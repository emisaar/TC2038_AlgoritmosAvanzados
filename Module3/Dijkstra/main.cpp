//  Actividad 3.2 - Implementación de "Dijkstra" y Floyd
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  main.cpp

#include <iostream>
#include "Graph.h"
#include <vector>

using namespace std;

int main() {
    vector<Node*> nodes;
    vector<Edge*> edges;

    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);
    Node *n5 = new Node(5);
    Node *n6 = new Node(6);
    nodes.push_back(n1);
    nodes.push_back(n2);
    nodes.push_back(n3);
    nodes.push_back(n4);
    nodes.push_back(n5);
    nodes.push_back(n6);

    edges.push_back(new Edge(n1, n2, 6));
    edges.push_back(new Edge(n1, n3, 2));
    edges.push_back(new Edge(n1, n6, 12));
    edges.push_back(new Edge(n2, n3, 7));
    edges.push_back(new Edge(n2, n4, 13));
    edges.push_back(new Edge(n3, n6, 1));
    edges.push_back(new Edge(n3, n4, 10));
    edges.push_back(new Edge(n4, n5, 5));
    edges.push_back(new Edge(n5, n6, 8));

    Graph *g = new Graph(nodes, edges);

    g->print();
    g->runDijkstra(n1);
    cout << "----------------" << endl;
    g->print();

    vector<Node*> nodesFloyd;
    vector<Edge*> edgesFloyd;

    Node *n1F = new Node(1);
    Node *n2F = new Node(2);
    Node *n3F = new Node(3);
    Node *n4F = new Node(4);
    nodesFloyd.push_back(n1F);
    nodesFloyd.push_back(n2F);
    nodesFloyd.push_back(n3F);
    nodesFloyd.push_back(n4F);

    edgesFloyd.push_back(new Edge(n1F, n2F, 2));
    edgesFloyd.push_back(new Edge(n1F, n3F, 2));
    edgesFloyd.push_back(new Edge(n1F, n4F, 3));
    edgesFloyd.push_back(new Edge(n2F, n1F, 2));
    edgesFloyd.push_back(new Edge(n2F, n3F, 1));
    edgesFloyd.push_back(new Edge(n2F, n4F, 5));
    edgesFloyd.push_back(new Edge(n3F, n1F, 2));
    edgesFloyd.push_back(new Edge(n3F, n2F, 1));
    edgesFloyd.push_back(new Edge(n3F, n4F, 4));
    edgesFloyd.push_back(new Edge(n4F, n1F, 3));
    edgesFloyd.push_back(new Edge(n4F, n2F, 5));
    edgesFloyd.push_back(new Edge(n4F, n3F, 4));

    Graph *gF = new Graph(nodesFloyd, edgesFloyd);

    cout << "Floyd" << endl;
    gF->runFloyd();

    return 0;
}