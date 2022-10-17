//  Actividad 3.3
//  Flujo Máximo
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 17/10/2022
//
//  Referencias:
//  https://favtutor.com/blogs/ford-fulkerson-algorithm
//  https://github.com/fit-coder/fitcoderyoutube/blob/master/graph/ford_fulkerson.cpp
//  https://www.programiz.com/dsa/ford-fulkerson-algorithm
//  https://github.com/BedirT/Algorithms_and_DS/blob/master/Algorithms/Graph/Ford%20Fulkerson.cpp
//  https://www.youtube.com/watch?v=_UcOALraATY

//https://brilliant.org/wiki/ford-fulkerson-algorithm/
//https://emory.gitbook.io/dsa-java/network-flow/ford-fulkerson-algorithm

#include "Graph.h"
#include <iostream>
using namespace std;

int main() {
    cout << "FORD-FULKERSON: " << endl;
    cout << "Dame el número de vértices: \n";
    int n; cin >> n;
    cout << "Dame la matriz que representa el grafo: \n";
    
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
     */
    cout << "Dame el inicio y el final: \n";
    int s, t;
    cin >> s >> t;
    int res = g->FordFulkerson(s, t);
    cout << "Respuesta: " << res << endl;
}

/*
 0 8 0 0 3 0
 0 0 9 0 0 0
 0 0 0 0 7 2
 0 0 0 0 0 5
 0 0 7 4 0 0
 0 0 0 0 0 0
 */

/* MUY LARGO, NO SE SI SIRVA
 6
 
0 16 13 0 0 0
0 0 10 12 0 0
0 4 0 0 14 0
0 0 9 0 0 20
0 0 0 7 0 4
0 0 0 0 0 0
 
 1 5
 */






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
*/
