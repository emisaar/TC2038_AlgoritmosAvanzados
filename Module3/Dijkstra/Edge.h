//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  Edge.h

#pragma once
#include "Node.h"

class Edge {
    public: 
        Node *first;
        Node *second;
        int weight;

        Edge(Node *_first, Node *_second, int _weight);
};