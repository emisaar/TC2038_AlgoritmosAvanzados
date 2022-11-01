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

#include "Edge.hpp"

//CONSTRUCTOR: Recibimos el nodo salida, el nodo llegada
//y el costo de la arista
Edge::Edge(Node* _first, Node* _second, int _weight, int _capacity){
    first = _first;
    second = _second;
    weight = _weight;
    capacity = _capacity;
}
