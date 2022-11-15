//  Actividad Integradora 2
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 17/11/2022


#include "Edge.hpp"

/*
Constructor de Edge (Arista)
    Recibe como parámetros:
    - Dos nodos:
        > nodo de salida (first)
        > nodo de llegada (second)
    - Ponderación o peso de la arista (weight)
*/
Edge::Edge(Node *_first, Node *_second, int _weight){
    first = _first;
    second = _second;
    weight = _weight;
}
