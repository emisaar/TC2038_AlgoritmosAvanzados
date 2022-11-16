//  Actividad 3.3
//  Implementación de "Knapsack problem"
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 03/11/2022

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
    
    //Constructores
    Graph(vector<vector<int>> matGraph);
    Graph(vector<Node*> _nodes, vector<Edge*> _edges);
    
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

    //Función que encuentra la arista que conecta u y v (si existe)
    Edge* findEdge2(int u, int v);
    
    //Función que encuentra el nodo con el id int node (si existe)
    Node* findNode(int node);
    
    //Función para realizar el recorrido BFS de un grafo
    bool bfs(Node *s, Node *t);
    
    //Función para encontrar a los vecinos de n
    vector<Node*> getNeighbors2(Node* n);
    
    //Función que resuelve The Knapsack Problem
    void findPaths(Node *s, Node *t, vector<int> &weights, vector<int> &values);
    
    //Función para imprimir las aristas del grafo
    void printGraph();

    vector<vector<Node*>> sets;
    void makeSet(Node* n);
    vector<Node*> findSet(Node* n);
    void doUnion(vector<Node*> a, vector<Node*> b);
    static bool compareWeight(Edge* a, Edge* b);

    void runKruskal();
};


#endif /* Graph_hpp */
