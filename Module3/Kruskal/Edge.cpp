//  Actividad 3.3
//  Implementación de "Knapsack problem"
//
//  Alejandro Díaz Villagómez | A01276769
//  Emiliano Saucedo Arriola  | A01659258
//
//  Fecha: 03/11/2022


#include "Edge.hpp"

//CONSTRUCTOR: Recibimos el nodo salida, el nodo llegada
//y el costo de la arista
Edge::Edge(Node *_first, Node *_second, int _weight){
    first = _first;
    second = _second;
    weight = _weight;
}
