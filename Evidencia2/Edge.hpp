//  Actividad 3.2
//  Implementación de "Dijkstra y Floyd"
//
//  Alejandro Díaz Villagómez | A01276769
//
//  Fecha: 06/10/2022
//
//  Referencias:

#ifndef Edge_hpp
#define Edge_hpp

#pragma once
#include "Node.hpp"

class Edge {
    public:
        Node *first;
        Node *second;
        int weight;
        int flow;

        Edge(Node *_first, Node *_second, int _weight);
};

#endif /* Edge_hpp */
