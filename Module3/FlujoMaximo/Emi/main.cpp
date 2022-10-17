//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  main.cpp

/* Instrucciones:
Escribe un programa en C++ que implemente los algoritmos de Dijkstra y Floyd para encontrar 
la distancia más corta entre parejas de nodos en un grafo dirigido. 

El programa debe leer un numero n seguido de n x n valores enteros no negativos que representan 
una matriz de adyacencias de un grafo dirigido.
El primer número representa el número de nodos, los siguientes valores en la matriz, el valor 
en la posición (i, j) representan el peso de la arista del nodo i al nodo j. Si no hay una arista 
entre el nodo i y el nodo j, el valor en la matriz debe ser -1.

La salida del programa es, primero con el algoritmo de Dijkstra la distancia del nodo i al nodo j 
para todos los nodos, y luego, la matriz resultado del algoritmo de Floyd.
*/

/* Teoría
Dijkstra: Algoritmo utilizado para encontrar los caminos más cortos desde un nodo de origen hasta 
los demás vértices en un determinado grafo.

Floyd: Algoritmo utilizado para encontrar las distancias más cortas entre cada par de vértices 
en un grafo dirigido ponderado por arista.

Referencias:
https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
https://www.youtube.com/watch?v=oNI0rf2P9gE
*/

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
        gFloyd->runFordFulkerson(nodes[0], nodes[5]);

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

        cout << "Dijkstra" << endl;
        for(int i = 0; i < n; i++) {
            vector<Node*> nodesDijkstra = createNodes(n);
            vector<Edge*> edgesDijkstra = createEdges(weightMatrix, nodesDijkstra);
            
            Graph *gDijkstra = new Graph(nodesDijkstra, edgesDijkstra);
            gDijkstra->runDijkstra(nodesDijkstra[i]);
            gDijkstra->printDijkstra();
            cout << endl;
        }

        cout << "Floyd" << endl;
        vector<Node*> nodesFloyd = createNodes(n);
        vector<Edge*> edgesFloyd = createEdges(weightMatrix, nodesFloyd);
        Graph *gFloyd = new Graph(nodesFloyd, edgesFloyd);
        gFloyd->runFloyd();
    }


    return 0;
}