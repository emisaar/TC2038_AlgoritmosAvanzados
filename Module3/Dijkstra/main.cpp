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
        row.push_back(0);
        row.push_back(2);
        row.push_back(-1);
        row.push_back(3);
        weightMatrix.push_back(row);
        row.clear();

        row.push_back(-1);
        row.push_back(0);
        row.push_back(1);
        row.push_back(5);
        weightMatrix.push_back(row);
        row.clear();

        row.push_back(2);
        row.push_back(3);
        row.push_back(0);
        row.push_back(-1);
        weightMatrix.push_back(row);
        row.clear();
        
        row.push_back(3);
        row.push_back(-1);
        row.push_back(4);
        row.push_back(0);
        weightMatrix.push_back(row);
        row.clear();


        cout << "\nMatriz de entrada" << endl;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                cout << weightMatrix[i][j] << "|";
            }
            cout << endl;
        }

        cout << "\nDijkstra" << endl;
        for(int i = 0; i < 4; i++) {
            vector<Node*> nodesDijkstra = createNodes(4);
            vector<Edge*> edgesDijkstra = createEdges(weightMatrix, nodesDijkstra);
            
            Graph *gDijkstra = new Graph(nodesDijkstra, edgesDijkstra);
            gDijkstra->runDijkstra(nodesDijkstra[i]);
            gDijkstra->printDijkstra();
            cout << endl;
        }

        cout << "\nFloyd" << endl;
        vector<Node*> nodesFloyd = createNodes(4);
        vector<Edge*> edgesFloyd = createEdges(weightMatrix, nodesFloyd);
        Graph *gFloyd = new Graph(nodesFloyd, edgesFloyd);
        gFloyd->runFloyd();

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