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

#ifndef Edge_hpp
#define Edge_hpp

#include "Node.hpp"
#include <stdio.h>

class Edge{
public:
    //Puntero de nodo de salida
    Node* first;
    
    //Puntero de nodo de llegada
    Node* second;
    
    //variable que representa el peso/costo de traslado
    int weight;
    
    //Valor de capacidad para algoritmo de Ford-Fulkerson
    int capacity;
    
    //Constructor
    Edge(Node* _first, Node* _second, int _weight, int _capacity);
};

#endif /* Edge_hpp */
