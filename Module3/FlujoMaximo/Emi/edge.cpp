//  Actividad 3.2 - Implementación de "Dijkstra" y "Floyd"
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  edge.cpp

#include "Edge.h"

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
    flow = 0;
}