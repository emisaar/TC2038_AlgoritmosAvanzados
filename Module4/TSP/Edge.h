//  Actividad 3.3
//  Implementación de "Knapsack problem"
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 03/11/2022

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
