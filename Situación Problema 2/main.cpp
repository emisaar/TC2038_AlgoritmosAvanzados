//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 07/11/2022

#include "Graph.hpp"
#include "DisjointSets.hpp"
#include <iostream>
using namespace std;

void FindMaxProfit(int W, vector<int> &weights, vector<int> &values);

int main() {
    cout << "DIJKSTRA AND FLOYD-WARSHALL ALGORITHM: " << endl;
    int n; cin >> n;
    
    vector<vector<int>> matGraph;
    for (int i = 0; i < n; i++){
        vector<int> row;
        for (int j = 0; j < n; j++){
            int input; cin >> input;
            row.push_back(input);
        }
        matGraph.push_back(row);
    }
    
    Graph* g = new Graph(matGraph);
    /*
    g->Dijkstra();
    g->FloydWarshall();
    cout << g->runFordFulkerson(1, (int)matGraph.size()) << endl;
     */
    
    
    /*
    cout << "Knapsack problem\n\nINPUT:\n";
    // LECTURA DE DATOS
    // N = Número de elementos
    // V = Valores de los elementos
    // P = Pesos de los elementos
    // W = Peso máximo
    int N, W;
    cin >> N;
    int pesos[N], valores[N];
    for (int i = 0; i < N; i++){
        cin >> valores[i];
    }
    
    for (int i = 0; i < N; i++){
        cin >> pesos[i];
    }
    
    cin >> W;
    cout << endl;
    
    // CREAMOS EL GRAFO
    vector<Node *> nodes;
    vector<Edge *> edges;
    for (int i = 0; i < N; i++){
        Node *n = new Node(valores[i]);
        nodes.push_back(n);
    }
    // Representa el nodo "x"
    nodes.push_back(new Node(1000));
    
    for (int i = 0; i < nodes.size() - 1; i++){
        for (int j = i + 1; j < nodes.size(); j++){
            // if (j == nodes.size() - 1) break;
            // Edge *e = new Edge(nodes[i], nodes[j], pesos[i] * -1);
            Edge *e = new Edge(nodes[i], nodes[j], pesos[i]);
            edges.push_back(e);
        }
    }
    
    Graph *g = new Graph(nodes, edges);
    vector<int> weights;
    vector<int> values;
    //    cout << "Edges" << endl;
    //    g->printGraph();
    cout << endl;
    for (int i = 0; i < nodes.size() - 1; i++){
        g->findPaths(nodes[i], nodes[N], weights, values);
    }
    
    cout << "weights " << weights.size() << endl;
    for (int i = 0; i < weights.size(); i++){
        cout << "weight: " << weights[i] << " value: " << values[i] << endl;
    }
    
    FindMaxProfit(W, weights, values);
    */
}

void FindMaxProfit(int W, vector<int> &weights, vector<int> &values){
    pair<int, int> maxProfit;
    maxProfit = make_pair(-1000, -1000);
    for (int i = 0; i < weights.size(); i++){
        if (weights[i] <= W and values[i] > maxProfit.second)
            maxProfit = make_pair(weights[i], values[i]);
    }
    
    cout << "OUTPUT:\n\tGanancia Máxima: " << maxProfit.second << "\n\tPeso en la mochila: " << maxProfit.first << "\n\n";
}

/*
input
4
0 2 -1 3
-1 0 1 5
2 3 0 -1
3 -1 4 0
 
 
 *Dijkstra marcará error!!*
4
0 5 -1 10
-1 0 3 -1
-1 -1 0 1
-1 -1 -1 0
 
 
 runFordFulkerson
6
0 16 13 0 0 0
0 0 10 12 0 0
0 4 0 0 14 0
0 0 9 0 0 20
0 0 0 7 0 4
0 0 0 0 0 0
 
 
Tarea 3.3 -> matriz
4
0 4 4 4
0 0 5 5
0 0 0 1
0 0 0 0
 
 R = 3
3
1
2
3
4
5
1
4
 
 R = 70
4
10
40
30
20
4
3
5
2
8
*/
