//  Actividad 3.2 - Implementación de "Dijkstra" y Floyd
//  Emiliano Saucedo Arriola  |  A01659258
//  Fecha: 06/10/2022
//  edge.cpp

#include "Edge.h"

Edge::Edge(Node *_first, Node *_second, int _weight){
    first = _first;
    second = _second;
    weight = _weight;
}