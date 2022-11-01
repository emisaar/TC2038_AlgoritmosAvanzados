//  Actividad 3.2 - Implementación de "Knapsack problem"
//  Alejandro Díaz Villagómez  |  A01276769
//  Emiliano Saucedo Arriola   |  A01659258
//  Fecha: 03/11/2022
//  main.cpp

#include <iostream>
#include "Graph.h"
#include <vector>

using namespace std;

#define tam 10000

int main()
{
    // LECTURA DE DATOS
    // N = Número de elementos
    // V = Valores de los elementos
    // P = Pesos de los elementos
    // W = Peso máximo
    int N, W;
    cin >> N;
    int pesos[N], valores[N];
    for (int i = 0; i < N; i++)
    {
        cin >> valores[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> pesos[i];
    }
    cin >> W;

    // CREAMOS EL GRAFO
    vector<Node *> nodes;
    vector<Edge *> edges;
    for (int i = 0; i < N; i++)
    {
        Node *n = new Node(valores[i]);
        nodes.push_back(n);
    }
    // Representa el nodo "x"
    nodes.push_back(new Node(1000));

    for (int i = 0; i < nodes.size() - 1; i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
        {
            // if (j == nodes.size() - 1) break;
            // Edge *e = new Edge(nodes[i], nodes[j], pesos[i] * -1);
            Edge *e = new Edge(nodes[i], nodes[j], pesos[i]);
            edges.push_back(e);
        }
    }

    Graph *g = new Graph(nodes, edges);
    g->runFordFulkerson(nodes[0], nodes[N + 1]);
}