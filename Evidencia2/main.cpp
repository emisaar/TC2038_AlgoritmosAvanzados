//  Actividad 3.2
//  Implementación de "Dijkstra y Floyd"
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 06/10/2022

#include "Graph.hpp"
#include <iostream>
using namespace std;

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
    
//    g->Dijkstra();
//    g->FloydWarshall();
    cout << g->runFordFulkerson(1, (int)matGraph.size()) << endl;
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
 
 
Tarea 3.3
4
0 4 4 4
0 0 5 5
0 0 0 1
0 0 0 0
*/
