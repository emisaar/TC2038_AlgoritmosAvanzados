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

#ifndef Graph_h
#define Graph_h

#include "Edge.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Graph{
public:
    //Recibimos la estructura del grafo, es decir, nodos y aristas
    vector<Node*> nodes;
    vector<Edge*> edges;
    
    //Constructor
    Graph(vector<vector<int>> matGraph);
    
    //Función para encontrar a los vecinos de n
    vector<Node*> getNeighbors(vector<Node*> Q, Node* n);
    
    //Función de impresión del recorrido de Dijkstra
    void printDijkstra(Node* source);
    
    //Función que hace el recorrido de Dijkstra en un nodo
    void runDijkstra(Node* source);
    
    //Función que hace el recorrido de Dijkstra para todos los nodos
    void Dijkstra();
    
    //Función para encontrar el nodo con la menor distancia
    Node* getMinDist(vector<Node*> qs);
    
    //Función para eliminar el nodo con la menor distancia
    void remove(vector<Node*> &qs, Node* q);
    
    //Getter para obtener el costo de la arista de u y v
    int getLength(Node* u, Node* v);
    
    //Función que calcula el camino más corto con el algoritmo Floyd-Warshall
    void FloydWarshall();
    
    Node* getSource(int source);
    Node* getSink(int sink);
    Node* getVertex(Node* nd);
    bool containsNode(Node* nd);
    
    vector<Edge*> getPath(Node* source, Node* sink, vector<Edge*> &path);
    bool containsEdge(vector<Edge*> path);
    int findMinFlow(vector<Edge*> path);
    int FordFulkerson(int s, int t);
};


#endif /* Graph_hpp */
