//  Actividad 3.2
//  Implementación de "Dijkstra y Floyd"
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 06/10/2022
//
//  Referencias:
//  https://www.youtube.com/watch?v=oNI0rf2P9gE
//  https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/

#ifndef Graph_hpp
#define Graph_hpp

#pragma once
#include "Edge.hpp"
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
    
    //Función para encontrar a los vecinos de n en un vector Q
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
    
    //Función que calcula el flujo máximo con el algoritmo Ford-Fulkerson
    int runFordFulkerson(int source, int sink);
    
    //Función que encuentra la arista que conecta u y v (si existe)
    Edge* findEdge(Node *u, Node *v);
    
    //Función que encuentra el nodo con el id int node (si existe)
    Node* findNode(int node);
    
    //Función para realizar el recorrido BFS de un grafo
    bool bfs(Node *s, Node *t);
    
    //Función para encontrar a los vecinos de n
    vector<Node*> getNeighbors2(Node* n);
    
    //Función que resuelve The Knapsack Problem
    void findPaths(Node *s, Node *t, vector<int> &weights, vector<int> &values);
};


#endif /* Graph_hpp */
