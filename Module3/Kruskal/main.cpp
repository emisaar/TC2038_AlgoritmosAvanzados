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

#include <iostream>
#include "Graph.hpp"
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
            while(a < -1) {
                cout << "Opción inválida. Solo valores enteros no negativos. (-1 es válido)" << endl;
                cout << "Peso[" << r + 1 << "][" << c + 1 << "]: ";
                cin >> a;
            }
            cout << endl;
            row.push_back(a);
        }
    matrix.push_back(row);
    }
    return matrix;
}

vector<Node*> createNodes(int n) {
    vector<Node*> nodes;
    for(int i = 0; i < n; i++) {
        Node *N = new Node(i + 1);
        nodes.push_back(N);
    }
    return nodes;
}

vector<Edge*> createEdges(vector<vector<int> > weightMatrix, vector<Node*> nodes) {
    vector<Edge*> edges;
    for(int i = 0; i < weightMatrix.size(); i++) {
        for(int j = 0; j < weightMatrix[0].size(); j++) {
            if(weightMatrix[i][j] != -1 && weightMatrix[i][j] != 0) {
                edges.push_back(new Edge(nodes[i], nodes[j], weightMatrix[i][j]));
            }
        }
    }
    return edges;
}

int main() {
    int n;
    string exec;
    cout << "¿Ejecutar caso de prueba (0) o ingresar valores de forma manual? (1): ";
    cin >> exec;

    while(exec != "0" && exec != "1") {
        cout << "Opción inválida. Intente de nuevo." << endl;
        cout << "¿Ejecutar caso de prueba (0) o ingresar valores de forma manual? (1): ";
        cin >> exec;
    }

    if(exec == "0") {
        vector<vector<int> > weightMatrix;
        vector<int> row;

        // 0
        row.push_back(0);
        row.push_back(16);
        row.push_back(13);
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        weightMatrix.push_back(row);
        row.clear();

        // 1
        row.push_back(0);
        row.push_back(0);
        row.push_back(10);
        row.push_back(12);
        row.push_back(0);
        row.push_back(0);
        weightMatrix.push_back(row);
        row.clear();

        // 2
        row.push_back(0);
        row.push_back(4);
        row.push_back(0);
        row.push_back(0);
        row.push_back(14);
        row.push_back(0);
        weightMatrix.push_back(row);
        row.clear();
        
        // 3
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        row.push_back(20);
        weightMatrix.push_back(row);
        row.clear();

        // 4
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        row.push_back(7);
        row.push_back(0);
        row.push_back(4);
        weightMatrix.push_back(row);
        row.clear();

        // 5
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        row.push_back(0);
        weightMatrix.push_back(row);
        row.clear();


        cout << "\nMatriz de entrada" << endl;
        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 6; j++) {
                cout << weightMatrix[i][j] << "|";
            }
            cout << endl;
        }

        vector<Node*> nodes = createNodes(6);
        vector<Edge*> edges = createEdges(weightMatrix, nodes);
        Graph *gFloyd = new Graph(nodes, edges);
        // cout << "FORD FULKERSON "<< gFloyd->runFordFulkerson(nodes[0], nodes[5]) << endl;

    } else {
        cout << "Introduce el número de nodos: ";
        cin >> n;

        cout << "Introduce los pesos del grafo." << endl;
        vector<vector<int> > weightMatrix = createMatrix(n);

        cout << "Matriz de entrada" << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << weightMatrix[i][j] << "|";
            }
            cout << endl;
        }
        
        vector<Node*> nodes = createNodes(n);
        vector<Edge*> edges = createEdges(weightMatrix, nodes);
        Graph *g = new Graph(nodes, edges);
        cout << "Kruskal" << endl;
        g->runKruskal();

        cout << "Floyd" << endl;
        g->FloydWarshall();

        // cout << "FORD FULKERSON "<< gFloyd->runFordFulkerson(nodes[0], nodes[5]) << endl;
    }


    return 0;
}

/*
4
0 16 45 32
16 0 18 21
45 18 0 7
32 21 7 0

*/